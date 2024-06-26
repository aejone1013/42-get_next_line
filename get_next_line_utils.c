/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <marvin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:47:06 by jaoh              #+#    #+#             */
/*   Updated: 2024/05/24 15:36:24 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
	}
	if (*ptr == (char)c)
		return (ptr);
	else
		return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	size;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = malloc(sizeof(char) * size);
	if (dest == NULL)
		return (NULL);
	while (*s1)
		*dest++ = *s1++;
	while (*s2)
		*dest++ = *s2++;
	*dest = '\0';
	return (dest - size + 1);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len_src;

	len_src = ft_strlen(src);
	if (size < 1)
		return (len_src);
	size -= 1;
	while (*src && size--)
		*dest++ = *src++;
	*dest = '\0';
	return (len_src);
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*dest;

	i = 1;
	while (s1[i - 1])
		i++;
	dest = malloc(sizeof(*s1) * i);
	i = 0;
	if (!dest)
		return (NULL);
	while (s1[i] && i < (n - 1))
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
