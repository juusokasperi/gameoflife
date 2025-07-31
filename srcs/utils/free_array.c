/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:40:28 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/31 15:29:47 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

/*
	Resource cleanup.
*/
void	free_array(t_state *state)
{
	for (size_t y = 0; y < state->height; ++y)
	{
		free(state->current_map[y]);
		free(state->next_map[y]);
		state->current_map[y] = NULL;
		state->next_map[y] = NULL;
	}
	free(state->current_map);
	free(state->next_map);
	state->current_map = NULL;
	state->next_map = NULL;
}
