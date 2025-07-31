/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:59:18 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/31 18:24:16 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

static void	prepare_state(t_state *state, int32_t fd);
static void	elapsed_time(struct timeval *start, struct timeval *end);
static void	basic_validation(int argc, char **argv, int32_t *fd, int32_t *iterations);

int	main(int argc, char **argv)
{
	t_state	state;
	int32_t	iterations;
	int32_t	fd;
	struct timeval start, end;

	basic_validation(argc, argv, &fd, &iterations);
	gettimeofday(&start, NULL);
	prepare_state(&state, fd);
	play_game(&state, iterations);
	print_state(&state);
	free_array(&state);
	gettimeofday(&end, NULL);
	elapsed_time(&start, &end);
	return (0);
}

/*
	Checks that the program is called with right amount of arguments,
	the iterations is a valid integer and the initial_state is a readable file.
*/
static void	basic_validation(int argc, char **argv, int32_t *fd, int32_t *iterations)
{
	if (argc != 3)
		invalid_format(argv[0]);
	*iterations = check_valid_iterations(argv[2]);
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
	check_size_and_validness(state, fd);
	allocate_memory(state, fd);
	initial_to_struct(state, fd);
	close(fd);
}
