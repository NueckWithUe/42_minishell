/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:44:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/01 15:04:39 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_printf(const char *f, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	va_start(ap, f);
	while (*f)
	{
		if (*f == '%')
		{
			f++;
			if (*f == '\0')
				break ;
			if (*f == '%')
				len += write(1, &*f, 1);
			else
				len += ft_format(*f, ap);
		}
		else
			len += write(1, &*f, 1);
		f++;
	}
	va_end(ap);
	return (len);
}
