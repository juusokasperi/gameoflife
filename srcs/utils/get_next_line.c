/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:26:33 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/31 14:39:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin(char const *s1, char const *s2);
static char	*ft_substr(char const *s, unsigned int start, size_t len);
static char	*append(char *new_line, char *buffer);
static void	clean_buffer(char *buffer);
static char	*fetch_line(char *str);
static char	*read_buffer(int32_t fd, char *new_line, char *buffer);

char	*get_next_line(int32_t fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	new_line = NULL;
	new_line = read_buffer(fd, new_line, buffer);
	if (!new_line)
		return (ft_free((void **)&new_line));
	new_line = fetch_line(new_line);
	if (!new_line)
		return (ft_free((void **)&new_line));
	clean_buffer(buffer);
	return (new_line);
}

static char	*append(char *new_line, char *buffer)
{
	char	*result;

	if (!new_line)
	{
		new_line = calloc(1, 1);
		if (!new_line)
			return (NULL);
	}
	result = ft_strjoin(new_line, buffer);
	if (!result)
		return (ft_free((void **)&new_line));
	ft_free((void **)&new_line);
	return (result);
}

static void	clean_buffer(char *buffer)
{
	char	*ptr;
	int		start;

	ptr = strchr(buffer, '\n');
	if (!ptr)
	{
		bzero(buffer, BUFFER_SIZE + 1);
		return ;
	}
	start = (ptr - buffer) + 1;
	memmove(buffer, buffer + start, strlen(buffer + start) + 1);
	bzero(buffer + strlen(buffer), BUFFER_SIZE - strlen(buffer));
}

static char	*fetch_line(char *str)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = strchr(str, '\n');
	if (!ptr)
		len = strlen(str);
	else
		len = (ptr - str) + 1;
	line = ft_substr(str, 0, len);
	ft_free((void **)&str);
	if (!line)
		return (NULL);
	return (line);
}

static char	*read_buffer(int fd, char *new_line, char *buffer)
{
	int32_t		nb_read;

	if (buffer[0])
	{
		new_line = append(new_line, buffer);
		if (!new_line)
			return (NULL);
	}
	nb_read = 1;
	while (!new_line || strchr(new_line, '\n'))
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read <= 0)
			break ;
		buffer[nb_read] = '\0';
		new_line = append(new_line, buffer);
		if (!new_line)
			break ;
	}
	if (nb_read == -1)
		return (ft_free((void **)&new_line));
	return (new_line);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start > strlen(s))
		return (strdup(""));
	if (len > strlen(s + start))
		len = strlen(s + start);
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = 0;
	return (substr);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	result = (char *)malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}
