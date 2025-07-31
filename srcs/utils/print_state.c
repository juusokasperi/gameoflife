/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:40:11 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/31 17:58:07 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

/*
	Prints the state after the iterations.
*/
void	print_state(t_state *state)
{
	const char *on = ON;
	const char *off = OFF;
	int on_len = strlen(on);
	int off_len = strlen(off);

	for (size_t y = 0; y < state->height; ++y)
	{
		for (size_t x = 0; x < state->width; ++x)
		{
			if (GET_CELL(state->current_map, y, x))
				write(STDOUT_FILENO, on, on_len);
			else
				write(STDERR_FILENO, off, off_len);
		}
		write(STDOUT_FILENO, "\n", 1);
	}
}
