/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:34:04 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/31 18:19:18 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_of_life.h"

/*
	Prints out the usage instructions for the user.
*/
void	invalid_format(const char *binary_name)
{
	const char *usage = "Usage: ";
	const char *state_iterations = " <initial_state> <iterations>\n";
	write(STDERR_FILENO, usage, strlen(usage));
	write(STDERR_FILENO, binary_name, strlen(binary_name));
	write(STDERR_FILENO, state_iterations, strlen(state_iterations));
	exit(1);
}

/*
	Checks that the file is openable and readable
*/
int32_t	check_file_open(const char *initial_state)
{
	const char	*error = "Error: Invalid file.\n";
	int32_t		fd = open(initial_state, O_RDONLY);
	char		buffer[1];

	if (fd < 0)
	{
		write(STDERR_FILENO, error, strlen(error));
		exit(1);
	}
	if (read(fd, buffer, 1) == -1)
	{
		write(STDERR_FILENO, error, strlen(error));
		close(fd);
		exit(1);
	}
	fd_to_start(fd);
	return (fd);
}

/*
	Checks that the iterations string consists only digits, and is within bounds (0-2147483647)
*/
int32_t	check_valid_iterations(const char *iterations)
{
	long	value;
	char	*endptr = NULL;

	value = strtol(iterations, &endptr, 10);
	if (endptr == iterations || *endptr != '\0' || value < 0 || value > INT32_MAX)
	{
		const char *err;
		if (value < 0 || value > INT32_MAX)
			err = "Error: Invalid iterations (0-2147483647)\n";
		else if (*endptr != '\0')
			err = "Error: Invalid character in iterations field\n";
		write(STDERR_FILENO, err, strlen(err));
		exit(1);
	}
	return (value);
}

void	free_map(uint64_t **map, int32_t i)
{
	while (i > 0)
	{
		free(map[--i]);
		map[i] = NULL;
	}
	free(map);
}
