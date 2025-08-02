/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:40:11 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/02 17:53:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

/*
	Prints the state after the iterations.
*/
void	print_state(t_state *state)
{
	uint32_t width = state->width;
	uint32_t height = state->height;
	uint64_t *current_map = state->current_map;

	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			if (GET_CELL(current_map, y, x, width))
				write(STDOUT_FILENO, "X", 1);
			else
				write(STDERR_FILENO, ".", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
	}
}
