/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:15:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/03 11:43:26 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_skip(char *s, char c, int word_or_char)
{
	while (*s == c && *s != '\0' && word_or_char == 0)
		s++;
	while (*s != c && *s != '\0' && word_or_char == 1)
		s++;
	return (s);
}

int	ft_get_wc(char *str, char delimiter)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	str = ft_skip(str, delimiter, 0);
	while (str[i])
	{
		while (str[i] && str[i] == delimiter)
			i++;
		if (str[i])
			wc++;
		while (str[i] && str[i] != delimiter)
			i++;
	}
	return (wc);
}

static int	get_len(char *str, char delimiter)
{
	static int	i = 0;
	int			j;

	j = 0;
	while (str[i] == delimiter)
		i++;
	while (str[i] && str[i] != delimiter)
	{
		i++;
		j++;
	}
	return (j);
}

char	*ft_strtok(char *str, char delimiter)
{
	char		*token;
	static int	i = 0;
	int			j;

	j = 0;
	token = ft_calloc(get_len(str, delimiter), sizeof(char));
	while (str[i] == delimiter)
		i++;
	while (str[i] && str[i] != delimiter)
	{
		token[j] = str[i];
		i++;
		j++;
	}
	token[j] = '\0';
	return (token);
}
