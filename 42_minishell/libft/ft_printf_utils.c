/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:16:27 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/01 15:04:32 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_handlestr(va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (!str)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}

int	ft_format(char f, va_list ap)
{
	if (f == 'p' || f == 'i' || f == 'c' || f == 's'
		|| f == 'X' || f == 'x' || f == 'u' || f == 'd')
	{
		if (f == 's')
			return (ft_handlestr(ap));
		else
			return (ft_formint(f, ap));
	}
	return (0);
}
