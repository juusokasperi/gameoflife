/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_of_life.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:18:53 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/02 17:43:43 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_OF_LIFE_H
# define GAME_OF_LIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdint.h>
#include <sys/time.h>
#include "raylib.h"

#define	GET_CELL(map, y, x, width) (((map)[((y) * (width) + (x)) / 64] >> (((y) * (width) + (x)) % 64)) & 1ULL)
#define	SET_CELL(map, y, x, width) ((map)[((y) * (width) + (x)) / 64] |= (1ULL << (((y) * (width) + (x)) % 64)))
#define	CLEAR_CELL(map, y, x, width) ((map)[((y) * (width) + (x)) / 64]  &= ~(1ULL << (((y) * (width) + (x)) % 64)))
#define TOGGLE_CELL(map, y, x, width) ((map)[((y) * (width) + (x)) / 64] ^= (1ULL << (((y) * (width) + (x)) % 64)))

#define STAR_COUNT 100

#define MIN_GRID_X 80
#define MIN_GRID_Y 80
#define MAX_WIDTH 800
#define MAX_HEIGHT 600

#define ON "\033[0;97mX\033[0m"
#define OFF "\033[0;34m.\033[0m"

typedef struct	s_star
{
	int32_t	x;
	int32_t	y;
	Color	color;
}	t_star;

typedef struct	s_state
{
	uint64_t	*current_map;
	uint64_t	*next_map;
	uint32_t	width;
	uint32_t	height;
	uint32_t	cell_size;
	char		cell_born[10];
	char		cell_alive[10];
}	t_state;

int32_t	check_valid_iterations(const char *iterations);
void	check_valid_ruleset(const char *input, char *cell);
void	check_size_and_validness(t_state *state, int32_t fd);
void	allocate_memory(t_state *state, int32_t fd);
void	initial_to_struct(t_state *state, int32_t fd,
		int32_t original_width, int32_t original_height);
void	play_game(t_state *state, int32_t iterations);

void	*ft_free(void **ptr);
void	fd_to_start(int32_t fd);
void	invalid_format(const char *binary_name);
int		check_file_open(const char *initial_state);
void	free_array(t_state *state);
void	ft_usleep(size_t ms);

void draw_state(t_state *state, t_star *stars, bool key_toggle, Font font);
void prepare_window(t_state *state);
void	toggle_cells(t_state *state);
void	swap_maps(t_state *state);

#endif /* GAME_OF_LIFE_H */
