/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:37:50 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/01 14:47:26 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	*foundchar;

	foundchar = NULL;
	p = (unsigned char *)s;
	while (n--)
	{
		if (*p != (unsigned char)c)
			p++;
		else
		{
			foundchar = p;
			break ;
		}
	}
	return (foundchar);
}
