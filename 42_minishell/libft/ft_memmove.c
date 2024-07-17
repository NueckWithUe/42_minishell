/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:31:18 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/01 14:47:33 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*sorc;
	char	*dest;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	sorc = (char *)src;
	dest = (char *)dst;
	if (dest > sorc)
	{
		while (len-- > 0)
		{
			dest[len] = sorc[len];
		}
		return ((void *)dest);
	}
	while (i < len)
	{
		dest[i] = sorc[i];
		i++;
	}
	return ((void *)dest);
}
