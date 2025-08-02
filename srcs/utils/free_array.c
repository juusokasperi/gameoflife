/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:40:28 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/02 17:54:06 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

/*
	Resource cleanup.
*/
void	free_array(t_state *state)
{
	uint64_t *map;

	map = (state->current_map < state->next_map)
		? state->current_map : state->next_map;
	free(map);
	state->current_map = NULL;
	state->next_map = NULL;
}
