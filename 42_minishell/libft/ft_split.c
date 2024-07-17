/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:18:30 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/01 14:49:12 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*ft_skip(char *s, char c, int word_or_char)
{
	while (*s == c && *s != '\0' && word_or_char == 0)
		s++;
	while (*s != c && *s != '\0' && word_or_char == 1)
		s++;
	return (s);
}

static char	*ft_wlen(char *s, char c)
{
	char	*res;
	int		i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	res = ft_calloc(i + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int	ft_getwc(char *s, char c)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	s = ft_skip(s, c, 0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			wc++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (wc);
}

static char	**ft_free(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	*temp;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	res = ft_calloc(ft_getwc((char *)s, c) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	if (ft_strlen(s) == 0)
		return (res);
	temp = (char *)s;
	temp = ft_skip(temp, c, 0);
	while (*temp != '\0')
	{
		res[i] = ft_wlen(temp, c);
		if (!res[i])
			return (ft_free(res));
		temp = ft_skip(temp, c, 1);
		temp = ft_skip(temp, c, 0);
		i++;
	}
	return (res);
}
