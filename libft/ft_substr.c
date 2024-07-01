/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:26:02 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/01 14:49:51 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	ft_strnlen(const char *s, size_t len)
{
	const char	*ptr;

	ptr = s;
	while (*ptr && len)
	{
		ptr++;
		len--;
	}
	return (ptr - s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		start = ft_strlen(s);
	s += start;
	len = ft_strnlen(s, len);
	sub = (char *)ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (NULL);
	ft_memcpy(sub, (void *)s, len);
	return (sub);
}
