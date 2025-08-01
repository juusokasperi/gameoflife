/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cells.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:14:41 by jrinta-           #+#    #+#             */
/*   Updated: 2025/08/01 14:20:07 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

void	handle_default(uint64_t **current_map, uint64_t **next_map,
		uint32_t y, uint32_t x, int8_t neighbors)
{
	if (GET_CELL(current_map, y, x))
	{
		if (neighbors == 2 || neighbors == 3)
			SET_CELL(next_map, y, x);
		else
			CLEAR_CELL(next_map, y, x);
	}
	else
	{
		if (neighbors == 3)
			SET_CELL(next_map, y, x);
		else
			CLEAR_CELL(next_map, y, x);
	}
}

void	handle_replicator(uint64_t **current_map, uint64_t **next_map,
		uint32_t y, uint32_t x, int8_t neighbors)
{
	if (GET_CELL(current_map, y, x))
	{
		if (neighbors == 1 || neighbors == 3
			|| neighbors == 5 || neighbors == 7)
			SET_CELL(next_map, y, x);
		else
			CLEAR_CELL(next_map, y, x);
	}
	else
	{
		if (neighbors == 1 || neighbors == 3
			|| neighbors == 5 || neighbors == 7)
			SET_CELL(next_map, y, x);
		else
			CLEAR_CELL(next_map, y, x);
	}
}

void	handle_seeds(uint64_t **current_map, uint64_t **next_map,
		uint32_t y, uint32_t x, int8_t neighbors)
{
	if (GET_CELL(current_map, y, x))
		CLEAR_CELL(next_map, y, x);
	else
	{
		if (neighbors == 2)
			SET_CELL(next_map, y, x);
		else
			CLEAR_CELL(next_map, y, x);
	}
}

void	handle_highlife(uint64_t **current_map, uint64_t **next_map,
		uint32_t y, uint32_t x, int8_t neighbors)
{
	if (GET_CELL(current_map, y, x))
	{
		if (neighbors == 2 || neighbors == 3)
			SET_CELL(next_map, y, x);
		else
			CLEAR_CELL(next_map, y, x);
	}
	else
	{
		if (neighbors == 3 || neighbors == 6)
			SET_CELL(next_map, y, x);
		else
			CLEAR_CELL(next_map, y, x);
	}
}
