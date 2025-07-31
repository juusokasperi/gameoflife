/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:59:18 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/31 15:29:10 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

static void	prepare_state(t_state *state, const char *initial_state);

int	main(int argc, char **argv)
{
	t_state	state;
	int32_t	iterations;

	if (argc != 3)
		invalid_format(argv[0]);
	iterations = check_valid_iterations(argv[2]);
	prepare_state(&state, argv[1]);
	play_game(&state, iterations);
	print_state(&state);
	free_array(&state);
}

/*
	Prepares the struct for the game.
*/
static void	prepare_state(t_state *state, const char *initial_state)
{
	int32_t	fd = check_file_open(initial_state);

	check_size_and_validness(state, fd);
	allocate_memory(state, fd);
	initial_to_struct(state, fd);
	close(fd);
}
