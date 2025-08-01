/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:21:38 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/01 14:20:14 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

static int8_t	count_live_neighbors(int y, int x, t_state *state);
static void		calculate_next(t_state *state);
static t_star*	generate_stars(t_star *stars);

/*
	Iterates through the game n times as specified by the user.
*/
void	play_game(t_state *state, int32_t iterations)
{
	t_star stars[STAR_COUNT];

	generate_stars(stars);
	for (int32_t i = 0; i < iterations && !WindowShouldClose(); ++i)
	{
		calculate_next(state);
		uint64_t **tmp = state->current_map;
		state->current_map = state->next_map;
		state->next_map = tmp;
		draw_state(state, stars);
	}
	printf("%d iterations done.\n", iterations);
	while (!WindowShouldClose())
		draw_state(state, stars);
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
			if (ny >= 0 && ny < (int32_t)state->height
				&& nx >= 0 && nx < (int32_t)state->width)
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
			if (state->ruleset == 'd')
				handle_default(current_map, next_map, y, x, neighbors);
			else if (state->ruleset == 'r')
				handle_replicator(current_map, next_map, y, x, neighbors);
			else if (state->ruleset == 's')
				handle_seeds(current_map, next_map, y, x, neighbors);
			else if (state->ruleset == 'h')
				handle_highlife(current_map, next_map, y, x, neighbors);
		}
	}
}

static t_star*		generate_stars(t_star *stars)
{
	int32_t			screen_width = GetScreenWidth();
	int32_t			screen_height = GetScreenHeight();
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	SetRandomSeed((unsigned int)(tv.tv_sec ^ tv.tv_usec));

	for (int i = 0; i < STAR_COUNT; ++i)
	{
		stars[i].x = GetRandomValue(0, screen_width);
		stars[i].y = GetRandomValue(0, screen_height);
		stars[i].color = (Color){ 245, 245, 245, GetRandomValue(20, 150) };
	}
	return (stars);
}
