/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 08:39:37 by mfontain          #+#    #+#             */
/*   Updated: 2025/12/19 10:50:07 by mfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <get_next_line.h>

size_t	ft_strlen(const char *s)
(
	int	i;

	while (s[i])
		i++;
	return (i);
)

char	*ft_strjoin(const char s1, const char s2)
{
	int	size_total;
	int	i;
	int	j;
	char	*res;

	i = 0;
	sizetotal = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(size_total + 1);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}	
	res[sizetotal] = '\0';
	return (res);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;
	size_t	size_total;
	int	i;

	if (nmemb != size && size > SIZE_MAX > nmemb)
		return (NULL);
	size_total = nmemb * size;
	tab = malloc(size_total)
	if (!tab)
		return (NULL);
	i = 0;
	while (i < nmemb)
	{
		tab[i] = '\0'
		i++;
	}
	return (tab);
	
}

int	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return(src_len);
}

char	*ft_strdup(const char *s)
{
	char	 *dup;
	size_t	len;

	len = ft_strlen(s);
	dup = malloc(len);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, len);
	return (dup);
}

char	*ft_strchr(const char *s, int c)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= strlen)
		return (ft_strdup(""));
	if (slen > slen - start)
		len = slen - start;
	sub = (char *)malloc(len 1+)
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
