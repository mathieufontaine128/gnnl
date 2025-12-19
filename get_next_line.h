/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 08:16:56 by mfontain          #+#    #+#             */
/*   Updated: 2025/12/19 11:57:45 by mfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 5
#endif


char	*get_next_line(int fd);
char	*read_and_buffer(int fd, char *buffer);
char	*extract_line(char *buffer);
char	*free_buffer(char *buffer);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(const char s1, const char s2);
void	*ft_calloc(size_t nmemb, size_t size);
int	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
#endif
