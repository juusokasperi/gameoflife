/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:59:18 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/01 14:23:27 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

static void	prepare_state(t_state *state, int32_t fd);
static void	elapsed_time(struct timeval *start, struct timeval *end);
static void	basic_validation(int argc, char **argv, int32_t *fd,
		int32_t *iterations, char *ruleset);

int	main(int argc, char **argv)
{
	t_state	state;
	int32_t	iterations;
	int32_t	fd;
	char	ruleset;
	struct timeval start, end;

	basic_validation(argc, argv, &fd, &iterations, &ruleset);
	state.ruleset = ruleset;
	gettimeofday(&start, NULL);
	prepare_state(&state, fd);
	prepare_window(&state);
	play_game(&state, iterations);
	free_array(&state);
	gettimeofday(&end, NULL);
	CloseWindow();
	elapsed_time(&start, &end);
	return (0);
}

/*
	Checks that the program is called with right amount of arguments,
	the iterations is a valid integer and the initial_state is a readable file.
*/
static void	basic_validation(int argc, char **argv, int32_t *fd,
		int32_t *iterations, char *ruleset)
{
	if (argc < 3 || argc > 4)
		invalid_format(argv[0]);
	*iterations = check_valid_iterations(argv[2]);
	if (argc == 4)
		*ruleset = check_valid_ruleset(argv[3]);
	else
		*ruleset = 'd';
	*fd = check_file_open(argv[1]);
}

static void	elapsed_time(struct timeval *start, struct timeval *end)
{
	long seconds = end->tv_sec - start->tv_sec;
	long microseconds = end->tv_usec - start->tv_usec;
	if (microseconds < 0) {
		seconds -= 1;
		microseconds += 1000000;
	}
	printf("Time elapsed: %ld.%06lds\n", seconds, microseconds);
}

/*
	Prepares the struct for the game.
*/
static void	prepare_state(t_state *state, int32_t fd)
{
	int32_t	original_height;
	int32_t	original_width;

	check_size_and_validness(state, fd);
	original_height = state->height;
	original_width = state->width;
	state->width = (state->width >= MIN_GRID_X) ? state->width : MIN_GRID_X;
	state->height = (state->height >= MIN_GRID_Y) ? state->height : MIN_GRID_Y;
	allocate_memory(state, fd);
	initial_to_struct(state, fd, original_width, original_height);
	close(fd);
}
