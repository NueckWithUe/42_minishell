/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:25:10 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/01 15:04:16 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_numlen_base(unsigned long n, int base)
{
	size_t	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		len++;
		n /= base;
	}
	return (len);
}

char	*ft_dechex(unsigned long n, int low)
{
	char		*base;
	char		*num;
	size_t		len;

	if (n == 0)
		return ("0");
	len = ft_numlen_base(n, 16);
	num = ft_calloc(len + 1, sizeof(char));
	if (!num)
		return (NULL);
	num[len] = '\0';
	if (low == 1)
		base = "0123456789abcdef";
	else if (low == 0)
		base = "0123456789ABCDEF";
	while (len-- && n)
	{
		num[len] = base[n % 16];
		n = n / 16;
	}
	return (num);
}
