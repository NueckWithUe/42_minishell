/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:02:37 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/09 12:18:04 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_tokenize(char *input, char delimiter)
{
	int		i;
	int		wc;
	char	**tokens;

	i = 0;
	wc = ft_get_wc(input, delimiter);
	tokens = ft_calloc(wc + 2, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (i < wc)
	{
		tokens[i] = ft_strtok(input, delimiter);
		i++;
	}
	tokens[wc] = ft_strdup("EOFToken");
	tokens[wc + 1] = NULL;
	return (tokens);
}

char	**lexer(char *input)
{
	char	**tokens;

	tokens = NULL;
	if (input[0] == '\0')
	{
		tokens = malloc(sizeof(char *));
		tokens[0] = ft_strdup("EOFToken");
		tokens[1] = NULL;
		return (tokens);
	}
	tokens = ft_tokenize(input, ' ');
	return (tokens);
}
