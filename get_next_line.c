/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <marvin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:41:03 by jaoh              #+#    #+#             */
/*   Updated: 2024/06/04 15:20:55 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	find_newline(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

static char	*update_buffer(char *buffer)
{
	size_t	start;
	size_t	len;
	char	*new_buffer;

	start = find_newline(buffer);
	len = ft_strlen(buffer) - start;
	if (len == 0)
		return (free(buffer), NULL);
	new_buffer = malloc(sizeof(char) * len + 1);
	if (!new_buffer)
		return (free(buffer), NULL);
	ft_strlcpy(new_buffer, buffer + start, len + 1);
	return (free(buffer), new_buffer);
}

static char	*read_line(const char *buffer)
{
	size_t	len;
	char	*line;

	len = find_newline(buffer);
	line = malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, len + 1);
	return (line);
}

static char	*read_to_buffer(int fd, char *buffer)
{
	char	*temp;
	char	*new_buffer;
	int		bytes;

	temp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!temp)
		return (free(buffer), NULL);
	while (!ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), free(temp), NULL);
		if (bytes == 0)
			break ;
		temp[bytes] = '\0';
		new_buffer = ft_strjoin(buffer, temp);
		if (!new_buffer)
			return (free(buffer), free(temp), NULL);
		free(buffer);
		buffer = new_buffer;
	}
	return (free(temp), buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{	
		buffer = ft_strndup("", 0);
		if (!buffer)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
	}
	buffer = read_to_buffer(fd, buffer);
	if (!buffer || *buffer == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = read_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}
/*
int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break ;
        printf("%s",line);
        free(line);
    }
}*/
