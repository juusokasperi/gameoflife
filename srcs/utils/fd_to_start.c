/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_to_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:38:07 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/31 14:38:29 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

/*
	Rewind the read pointer back to start of file
*/
void	fd_to_start(int32_t fd)
{
	if (lseek(fd, 0, SEEK_SET) < 0)
	{
		const char	*lseek_err = "Error: Failed to set lseek() to 0.\n";
		write(STDERR_FILENO, lseek_err, strlen(lseek_err));
		close(fd);
		exit(1);
	}
}
