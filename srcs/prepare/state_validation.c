/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:16:02 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/31 15:05:44 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"
#include "get_next_line.h"

static int32_t get_line_width(char *line);
static void get_first_line(int32_t fd, uint32_t *width, uint32_t *height);

/*
	Checks that the map is a square and that it contains only
	valid characters '.' and 'X'
*/
void	check_size_and_validness(t_state *state, int32_t fd)
{
	state->width = 0;
	state->height = 0;
	int64_t	line_width = 0;
	char	*line = NULL;

	get_first_line(fd, &state->width, &state->height);
	line = get_next_line(fd);
	while (line)
	{
		line_width = get_line_width(line);
		ft_free((void **)&line);
		if (line_width == -1 || line_width != (int64_t)state->width)
		{
			char *err;
			if (line_width == -1)
				err = "Error: Map can only contain characters '.' and 'X'.\n";
			else
				err = "Map is not valid.\n";
			write(STDERR_FILENO, err, strlen(err));
			close(fd);
			exit(1);
		}
		state->height++;
		line = get_next_line(fd);
	}
	fd_to_start(fd);
}

/*
	Gets the first line which is then used as a comparison for the rest of the
	lines (width must match so the map is always a square)
*/
static void get_first_line(int32_t fd, uint32_t *width, uint32_t *height)
{
	char	*line = NULL;
	int32_t line_width = 0;

	line = get_next_line(fd);
	if (line == NULL)
	{
		const char *err = "Error: Unable to get first line from initial state.\n";
		write(STDERR_FILENO, err, strlen(err));
		close(fd);
		exit(1);
	}
	line_width = get_line_width(line);
	*height = 1;
	ft_free((void **)&line);
	if (line_width <= 0)
	{
		char	*err;
		if (line_width == -1)
			err = "Error: Map can only contain characters '.' and 'X'.\n";
		else
			err = "Error: Initial state width/height cannot be less than 1.\n";
		write(STDERR_FILENO, err, strlen(err));
		close(fd);
		exit(1);
	}
	*width = line_width;
}

/*
	Checks width of the line and validates that it contains only
	'.' AND 'X' characters.
*/
static int32_t get_line_width(char *line)
{
	int	i = -1;
	int	width = 0;

	while (line[++i])
	{
		if (line[i] != '.' && line[i] != 'X' && line[i] != '\n')
			return (-1);
		width++;
	}
	return (width);
}
