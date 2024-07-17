/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:43:40 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/01 14:49:12 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	x;
	size_t	y;

	x = 0;
	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	y = ft_strlen(dst);
	while ((src[x]) && (y + 1 < dstsize))
	{
		dst[y] = src[x];
		x++;
		y++;
	}
	dst[y] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[x]));
}
