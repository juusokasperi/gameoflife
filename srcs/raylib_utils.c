/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raylib_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:54:47 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/02 01:23:31y jrinta-          ###   ########.fr       */
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
	InitWindow(screen_width, screen_height, "Game of Life (T: Toggle Keys)");
	SetTargetFPS(10);
	printf("Screen size: %dx%d\t| Grid size:%dx%d\t| Cell_size %d\t| Ruleset: B%s/S%s\n",
		screen_width, screen_height, width, height, state->cell_size,
		state->cell_born, state->cell_alive);
}

void draw_state(t_state *state, t_star *stars, bool key_toggle, Font font)
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
	if (key_toggle)
		DrawTextEx(font, "P: Pause iterations, C: Continue iterations\n" "Click on cells to toggle ON/OFF", (Vector2){ 10, screen_height - 50 }, 18, 1, YELLOW);
	EndDrawing();
}

void	toggle_cells(t_state *state)
{
	Vector2 mouse = GetMousePosition();
	int32_t grid_x = (int32_t)mouse.x / state->cell_size;
	int32_t grid_y = (int32_t)mouse.y / state->cell_size;
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
		&& grid_x >= 0 && grid_x < (int32_t)state->width
		&& grid_y >= 0 && grid_y < (int32_t)state->height)
		TOGGLE_CELL(state->current_map, grid_y, grid_x);
}

void	swap_maps(t_state *state)
{
	uint64_t **tmp = state->current_map;
	state->current_map = state->next_map;
	state->next_map = tmp;
}
