/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:18:23 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/02 17:49:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"
#include "get_next_line.h"

/*
	Allocates memory for the array
*/
void	allocate_memory(t_state *state, int32_t fd)
{
	size_t		uints_per_map = (state->width * state->height + 63) / 64;
	uint64_t	*map = calloc(uints_per_map * 2, sizeof(uint64_t));

	if (map == NULL)
	{
		const char	*err = "Error: Malloc error in allocate_memory().\n";
		close(fd);
		write(STDERR_FILENO, err, strlen(err));
		exit(1);
	}
	state->current_map = map;
	state->next_map = map + uints_per_map;
}

/*
	Saves the initial state to current_map array.
*/
void	initial_to_struct(t_state *state, int32_t fd)
{
	char	*line = get_next_line(fd);
	int32_t	x;
	int32_t	y = 0;

	while (line)
	{
		x = -1;
		while (line[++x])
		{
			if (line[x] == 'X')
				SET_CELL(state->current_map, y, x, state->width);
			else
				CLEAR_CELL(state->current_map, y, x, state->width);
		}
		y++;
		ft_free((void **)&line);
		line = get_next_line(fd);
	}
}
