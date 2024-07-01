/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:44:45 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/01 14:47:24 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*ft_minmax(int n)
{
	if (n == INT32_MIN)
		return (ft_strdup("-2147483648"));
	if (n == INT32_MAX)
		return (ft_strdup("2147483647"));
	if (n == 0)
		return (ft_strdup("0"));
	return ("1");
}

static int	ft_numlen(int n)
{
	int	space;

	space = 0;
	while (n / 10 != 0)
	{
		space++;
		n = n / 10;
	}
	return (space + 1);
}

char	*ft_itoa(int n)
{
	char		*num;
	int			space;
	long int	nb;

	nb = (long int)n;
	space = ft_numlen(n);
	if (n == 0 || n == INT32_MAX || n == INT32_MIN)
		return (ft_minmax(nb));
	if (n < 0)
		space++;
	num = (char *)malloc(sizeof(char) * space + 1);
	if (!num)
		return (NULL);
	if (n < 0)
	{
		num[0] = '-';
		n = n * -1;
	}
	num[space] = '\0';
	while (n)
	{
		num[--space] = n % 10 + '0';
		n = n / 10;
	}
	return (num);
}
