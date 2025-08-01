/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raylib_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:54:47 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/01 14:22:58 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"
#include <math.h>

static void	determine_cell_size(t_state *state, uint32_t width, uint32_t height)
{
	int32_t	cell_size_w = MAX_WIDTH / width;
	int32_t	cell_size_h = MAX_HEIGHT / height;
	int32_t	cell_size = (cell_size_w < cell_size_h) ? cell_size_w : cell_size_h;
	if (cell_size < 5)
		cell_size = 5;
	else if (cell_size > 10)
		cell_size = 10;
	state->cell_size = cell_size;
}

void prepare_window(t_state *state)
{
	uint32_t	width = (state->width >= MIN_GRID_X) ? state->width : MIN_GRID_X;
	uint32_t	height = (state->height >= MIN_GRID_Y) ? state->height : MIN_GRID_Y;
	determine_cell_size(state, width, height);
	uint32_t	screen_width = width * state->cell_size;
	uint32_t	screen_height = height * state->cell_size;

	SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	InitWindow(screen_width, screen_height, "Game of Life");
	SetTargetFPS(10);
	printf("Screen size: %dx%d\t| Grid size:%dx%d\t| Cell_size %d\t| Ruleset: ", screen_width, screen_height, width, height, state->cell_size);
	if (state->ruleset == 'h')
		printf("B36/S23\n");
	else if (state->ruleset == 'r')
		printf("B1357/S1357\n");
	else if (state->ruleset == 's')
		printf("B2/S\n");
	else
		printf("B3/S23\n");
}

void draw_state(t_state *state, t_star *stars)
{
	int32_t	screen_width = GetScreenWidth();
	int32_t screen_height = GetScreenHeight();

	BeginDrawing();
	DrawRectangleGradientV(0, 0, screen_width, screen_height,
		(Color){ 10, 10, 40, 255 }, BLACK);

	for (size_t i = 0; i < STAR_COUNT; ++i)
		DrawPixel(stars[i].x, stars[i].y, stars[i].color);

	Color grid_color = (Color){ 30, 30, 60, 180 };
	Color grid_background = (Color){ 30, 30, 60, 100 };

	for (int32_t x = 0; x <= screen_width; ++x)
		DrawLine(x * state->cell_size, 0,
			x * state->cell_size, screen_height, grid_color);
	for (int32_t y = 0; y <= screen_height; ++y)
	{
		DrawLine(y * state->cell_size, 0,
			screen_width, y * state->cell_size, grid_background);
		DrawLine(0, y * state->cell_size,
			screen_width, y * state->cell_size, grid_color);
	}

	Color glow_color = (Color){ 200, 200, 50, 20 };
	for (uint32_t y = 0; y < state->height; ++y)
	{
		for (uint32_t x = 0; x < state->width; ++x)
		{
			int32_t	center_x = (x * state->cell_size) + state->cell_size / 2;
			int32_t center_y = (y * state->cell_size) + state->cell_size / 2;
			float radius = (state->cell_size - 2) / 2;
			if (GET_CELL(state->current_map, y, x))
			{
				DrawCircle(center_x, center_y, radius + 4, glow_color);
				DrawCircle(center_x, center_y, radius, RAYWHITE);
			}
		}
	}
	EndDrawing();
}
