/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:02:37 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/19 11:17:38 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static char	**ft_tokenize(char *input, char delimiter)
// {
// 	int		i;
// 	int		wc;
// 	char	**tokens;

// 	i = 0;
// 	wc = ft_get_wc(input, delimiter);
// 	tokens = ft_calloc(wc + 2, sizeof(char *));
// 	if (!tokens)
// 		return (NULL);
// 	while (i < wc)
// 	{
// 		tokens[i] = ft_strtok(input, delimiter);
// 		i++;
// 	}
// 	tokens[wc] = ft_strdup("EOFToken");
// 	tokens[wc + 1] = NULL;
// 	return (tokens);
// }

static char	**ft_tokenize(char *input, char delimiter)
{
	char	**tokens;
	int		wc;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	wc = ft_get_wc(input, delimiter);
	tokens = malloc(sizeof(char *) * (wc + 2));
	if (!tokens)
		return (NULL);
	while (i < wc)
	{
		tokens[i] = malloc(sizeof(char) * ft_strlen(input) + 1);
		while (input[j] &&input[j] == delimiter)
			j++;
		while (input[j] && input[j] != delimiter)
		{
			tokens[i][k] = input[j];
			j++;
			k++;
		}
		i++;
		k = 0;
	}
	tokens[wc] = ft_strdup("EOFToken");
	tokens[wc + 1] = NULL;
	return (tokens);
}

char	**lexer(char *input)
{
	char	**tokens;

	if (!input || input[0] == '\0')
	{
		tokens = (char **)malloc(sizeof(char *) * 2);
		tokens[0] = ft_strdup("EOFToken");
		tokens[1] = NULL;
		return (tokens);
	}
	tokens = ft_tokenize(input, ' ');
	return (tokens);
}
