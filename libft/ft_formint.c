/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:05:12 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/01 15:04:02 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void	ft_putunbr(unsigned int n)
{
	if (n >= 10)
	{
		ft_putunbr(n / 10);
		n %= 10;
	}
	if (n < 10)
		ft_putchar_fd(n + 48, 1);
}

static int	ft_numlen(int n)
{
	size_t	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	ft_handleuint(unsigned int u, char f)
{
	char	*res;

	if (f == 'X' || f == 'x')
	{
		if (f == 'X')
			res = ft_dechex(u, 0);
		else
			res = ft_dechex(u, 1);
		write(1, res, ft_strlen(res));
		if (u != 0)
			free(res);
		return ;
	}
	else
		ft_putunbr(u);
}

static int	ft_strptr(unsigned long s)
{
	char	*prefix;
	char	*num;
	char	*res;
	int		ret;

	ret = 0;
	if (!s)
		return (write(1, "0x0", 3));
	else
		prefix = "0x";
	num = ft_dechex(s, 1);
	res = ft_strjoin(prefix, num);
	free(num);
	ret += write(1, res, ft_strlen(res));
	free(res);
	return (ret);
}

int	ft_formint(char f, va_list ap)
{
	int				i;
	unsigned int	u;
	unsigned long	p;

	if (f == 'd' || f == 'i' || f == 'c')
	{
		i = va_arg(ap, int);
		if (f == 'c')
			return (write(1, &i, 1));
		ft_putnbr_fd(i, 1);
		return (ft_numlen(i));
	}
	else if (f == 'X' || f == 'x' || f == 'u')
	{
		u = va_arg(ap, unsigned int);
		ft_handleuint(u, f);
		if (f == 'u')
			return (ft_numlen_base(u, 10));
		return (ft_numlen_base(u, 16));
	}
	p = va_arg(ap, unsigned long);
	return (ft_strptr(p));
}
