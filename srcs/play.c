/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:21:38 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/01 18:30:17by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

//	Default B3/S23, Replicator B1357/S1357, Seeds B2/S, HighLife B36/S23

static char		count_live_neighbors(int y, int x, t_state *state);
static void		calculate_next(t_state *state);
static t_star*	generate_stars(t_star *stars);

/*
	Iterates through the game n times as specified by the user.
*/
void	play_game(t_state *state, int32_t iterations)
{
	bool	keys_toggle = false;
	bool	is_paused = false;
	t_star	stars[STAR_COUNT];
	int32_t	i = 0;
	Font inconsolata = LoadFont("./font/inconsolata.ttf");

	generate_stars(stars);
	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_P))
			is_paused = true;
		if (IsKeyPressed(KEY_C))
			is_paused = false;
		if (IsKeyReleased(KEY_T))
			keys_toggle = !keys_toggle;
		draw_state(state, stars, keys_toggle, inconsolata);
		if (is_paused)
			toggle_cells(state);
		if (!is_paused && i < iterations)
		{
			calculate_next(state);
			swap_maps(state);
			i++;
		}
		else if (!is_paused && i == iterations)
		{
			printf("%d iterations done.\n", iterations);
			i++;
		}
	}
	UnloadFont(inconsolata);
}

static char	count_live_neighbors(int y, int x, t_state *state)
{
	int32_t		count = 0;
	int32_t		width = state->width;
	int32_t		height = state->height;
	uint64_t	*current_map = state->current_map;

	for (int32_t dy = -1; dy <= 1; ++dy)
	{
		for (int32_t dx = -1; dx <= 1; ++dx)
		{
			if (dy == 0 && dx == 0)
				continue;
			int32_t ny = y + dy;
			int32_t nx = x + dx;
			if (ny >= 0 && ny < height
				&& nx >= 0 && nx < width)
				count += GET_CELL(current_map, ny, nx, width);
		}
	}
	return (count + '0');
}

static void calculate_next(t_state *state)
{
	uint64_t	*current_map = state->current_map;
	uint64_t	*next_map = state->next_map;
	uint32_t	width = state->width;
	uint32_t	height = state->height;

	for (uint32_t y = 0; y < height; ++y)
	{
		for (uint32_t x = 0; x < width; ++x)
		{
			char neighbors = count_live_neighbors(y, x, state);
			if (GET_CELL(current_map, y, x, width))
			{
				if (strchr(state->cell_alive, neighbors))
					SET_CELL(next_map, y, x, width);
				else
					CLEAR_CELL(next_map, y, x, width);
			}
			else
			{
				if (strchr(state->cell_born, neighbors))
					SET_CELL(next_map, y, x, width);
				else
					CLEAR_CELL(next_map, y, x, width);
			}
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
