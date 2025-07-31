/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:18:23 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/31 15:27:44 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"
#include "get_next_line.h"

/*
	Allocates memory for the 2D arrays
*/
void	allocate_memory(t_state *state, int32_t fd)
{
	size_t	uints_per_row = (state->width + 63) / 64;
	const char *err = "Error: Malloc error in allocate_memory().\n";

	state->current_map = calloc(state->height, sizeof(uint64_t*));
	state->next_map = calloc(state->height, sizeof(uint64_t*));
	if (state->current_map == NULL || state->next_map == NULL)
	{
		if (state->current_map)
			free(state->current_map);
		if (state->next_map)
			free(state->next_map);
		close(fd);
		write(STDERR_FILENO, err, strlen(err));
		exit(1);
	}
	for (size_t i = 0; i < state->height; ++i)
	{
		state->current_map[i] = calloc(uints_per_row, sizeof(uint64_t));
		if (state->current_map[i] == NULL)
		{
			free_map(state->current_map, i);
			free_map(state->next_map, i);
			close(fd);
			write(STDERR_FILENO, err, strlen(err));
			exit(1);
		}
		state->next_map[i] = calloc(uints_per_row, sizeof(uint64_t));
		if (state->next_map[i] == NULL)
		{
			free_map(state->current_map, i + 1);
			free_map(state->next_map, i);
			close(fd);
			write(STDERR_FILENO, err, strlen(err));
			exit(1);
		}
	}
}

/*
	Saves the initial state to current_map 2D array.
*/
void	initial_to_struct(t_state *state, int32_t fd)
{
	char	*line = get_next_line(fd);
	int		x;
	int		y = 0;

	while (line)
	{
		x = -1;
		while (line[++x])
		{
			if (line[x] == 'X')
				SET_CELL(state->current_map, y, x);
			else
				CLEAR_CELL(state->current_map, y, x);
		}
		y++;
		ft_free((void **)&line);
		line = get_next_line(fd);
	}
}
