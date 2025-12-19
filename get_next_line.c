/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:58:03 by mfontain          #+#    #+#             */
/*   Updated: 2025/12/19 13:41:48 by mfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*read_and_buffer(int fd, char *buffer)
{
	int	rd;
	char	*tmp;
	char	buf[BUFFER_SIZE + 1];

 	if (!buffer)
		buffer = ft_calloc(1, 1);
	if (!buffer)
		return (NULL);
	rd = read(fd, buf, BUFFER_SIZE);
	if (rd <= 0)
		return (NULL);
	buf[rd] = '\0';
	tmp = buffer;
	buffer = ft_strjoin(tmp, buf);
	free(tmp);
	return (buffer);
}
char	*extract_line(char *buffer)
{
	char	*line;
	int	i;
	int	len;

	if (!buffer || !*buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		len = i + 1;
	else
		len = i;		
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, len + 1);
	return (line);
}

char	*free_buffer(char *buffer)
{
	int	i;
	char	*new_buffer;

	if(!buffer || !*buffer)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	new_buffer = ft_strdup(buffer + i);
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char	*line;
	char	*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_calloc(1, 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(buffer, '\n'))
	{
		tmp = read_and_buffer(fd, buffer);
		if (!tmp)
		{
			if (!*buffer)
			{
				free(buffer);
				buffer = NULL;
				return (NULL);
			}
			break;
		}
		buffer = tmp;
	}
	line = extract_line(buffer);
	if (!line)
		return (NULL);
	tmp  = free_buffer(buffer);
	if (!tmp)
	{
		buffer = NULL;
		return (line);
	}
	buffer = tmp;
	return (line);
}
#include <fcntl.h>
#include <stdio.h>
int	main()
{
	int	fd;
	int	i;

	fd = open("cimetiere_marin.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	i = 0;
	while (i < 200)
	{
		char *line = get_next_line(fd);
		if (!line)
			break;
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd);
	//free(buffer);
	//buffer = NULL;
	return (0);
}
