/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:58:03 by mfontain          #+#    #+#             */
/*   Updated: 2025/12/18 22:44:06 by mfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef	BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

// utils functions
static size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*z;

	z = (unsigned char *)s;
	while (n > 0)
	{
		*z++ = '\0';
		n--;
	}
}
static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return((char *)s);
	return (NULL);
}
static size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	init_dest_len;
	size_t	src_len;
	
	i = 0;
	while (dest[i] && i < size)
		i++;
	init_dest_len = i;
	src_len = ft_strlen(src);
	if (size <= init_dest_len)
		return (src_len + size);
	j = 0;
	while (src[j] && (i + j) < size - 1)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (init_dest_len + src_len);
}

static size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < size -1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}
char	*ft_strdup(const char *s)
{
	char *dup;
	size_t	len;

	len = ft_strlen(s) + 1;
	dup = malloc(len);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, len);
	return (dup);
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;
	size_t	size_total;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	size_total = nmemb * size;
	tab = malloc(size_total);
	if (!tab)
		return (NULL);
	ft_bzero(tab, size_total);
	return (tab);
}
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*tab;
	size_t	tab_len;

	if (!s1 || !s2)
		return (NULL);
	tab_len = ft_strlen(s1) + ft_strlen(s2);
	tab = (char *)malloc((tab_len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s1, ft_strlen(s1) + 1);
	ft_strlcat(tab, s2, tab_len + 1);
	return (tab);
}
// core function
static char	*read_and_buffer(int fd, char *buffer)
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
static	char	*extract_line(char *buffer)
{
	// extrait une ligne du buffer jusqu'a \n
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

static char	*free_buffer(char *buffer)
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
