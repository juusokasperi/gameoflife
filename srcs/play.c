/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:21:38 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/31 17:48:16 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

static int8_t	count_live_neighbors(int y, int x, t_state *state);
static void 	calculate_next(t_state *state);

/*
	Iterates through the game n times as specified by the user.
*/
void	play_game(t_state *state, int32_t iterations)
{
	for (int32_t i = 0; i < iterations; ++i)
	{
		calculate_next(state);
		uint64_t **tmp = state->current_map;
		state->current_map = state->next_map;
		state->next_map = tmp;
		printf("\033[2J\033[H\n");
		print_state(state);
		ft_usleep(100);
	}
}

static int8_t	count_live_neighbors(int y, int x, t_state *state)
{
	int32_t	count = 0;
	for (int32_t dy = -1; dy <= 1; ++dy)
	{
		for (int32_t dx = -1; dx <= 1; ++dx)
		{
			if (dy == 0 && dx == 0)
				continue;
			int32_t ny = y + dy;
			int32_t nx = x + dx;
			if (ny >= 0 && ny < (int32_t)state->height && nx >= 0 && nx < (int32_t)state->width)
				count += GET_CELL(state->current_map, ny, nx);
		}
	}
	return (count);
}

static void calculate_next(t_state *state)
{
	uint64_t	**current_map = state->current_map;
	uint64_t	**next_map = state->next_map;

	for (uint32_t y = 0; y < state->height; ++y)
	{
		for (uint32_t x = 0; x < state->width; ++x)
		{
			int8_t	neighbors = count_live_neighbors(y, x, state);
			if (GET_CELL(current_map, y, x))
			{
				if (neighbors == 2 || neighbors == 3)
					SET_CELL(next_map, y, x);
				else
					CLEAR_CELL(next_map, y, x);
			}
			else
			{
				if (neighbors == 3)
					SET_CELL(next_map, y, x);
				else
					CLEAR_CELL(next_map, y, x);
			}
		}
	}
}
