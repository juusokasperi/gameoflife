/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raylib_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:54:47 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/01 01:28:37 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"
#include <math.h>

void prepare_window(t_state *state)
{
	state->cell_size = 7;
	SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	InitWindow(state->width * state->cell_size, state->height * state->cell_size, "Game of Life");
	SetTargetFPS(10);
}

void draw_state(t_state *state, t_star *stars, int32_t width, int32_t height)
{

	BeginDrawing();
	DrawRectangleGradientV(0, 0, width, height,
		(Color){ 10, 10, 40, 255 }, BLACK);
	for (size_t i = 0; i < STAR_COUNT; ++i)
		DrawPixel(stars[i].x, stars[i].y, RAYWHITE);

	for (uint32_t y = 0; y < state->height; ++y)
	{
		for (uint32_t x = 0; x < state->width; ++x)
		{
			if (GET_CELL(state->current_map, y, x))
				DrawRectangle(x * state->cell_size, y * state->cell_size,
					state->cell_size, state->cell_size, RAYWHITE);
		}
	}
	EndDrawing();
}
