/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:59:18 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/02 18:00:41 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

static void	prepare_state(t_state *state, int32_t fd);
static void	elapsed_time(struct timeval *start, struct timeval *end);
static void	basic_validation(int argc, char **argv, int32_t *fd,
		int32_t *iterations, t_state *state);
static void	free_map(t_state *state);

int	main(int argc, char **argv)
{
	t_state	state;
	int32_t	iterations;
	int32_t	fd;
	struct timeval start, end;

	basic_validation(argc, argv, &fd, &iterations, &state);
	gettimeofday(&start, NULL);
	prepare_state(&state, fd);
	play_game(&state, iterations);
	print_state(&state);
	free_map(&state);
	gettimeofday(&end, NULL);
	elapsed_time(&start, &end);
	return (0);
}

/*
	Checks that the program is called with right amount of arguments,
	the iterations is a valid integer and the initial_state is a readable file.
*/
static void	basic_validation(int argc, char **argv, int32_t *fd,
		int32_t *iterations, t_state *state)
{
	memset(state->cell_alive, '\0', 10);
	memset(state->cell_born, '\0', 10);
	if (argc < 3 || argc == 4 || argc > 5)
		invalid_format(argv[0]);
	*iterations = check_valid_iterations(argv[2]);
	if (argc == 5)
	{
		check_valid_ruleset(argv[3], state->cell_born);
		check_valid_ruleset(argv[4], state->cell_alive);
	}
	else
	{
		state->cell_born[0] = '3';
		state->cell_alive[0] = '2';
		state->cell_alive[1] = '3';
	}
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

static void	free_map(t_state *state)
{
	uint64_t	*map;

	map = (state->current_map < state->next_map)
		? state->current_map : state->next_map;
	free(map);
	state->current_map = NULL;
	state->next_map = NULL;
}
