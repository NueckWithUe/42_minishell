/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:02:37 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/03 12:25:02 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_list(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("Token Nr. %d: [%s]\n", i, arr[i]);
		i++;
	}
}

static char	**ft_tokenize(char *input, char delimiter)
{
	int		i;
	int		wc;
	char	**tokens;

	i = 0;
	wc = ft_get_wc(input, delimiter);
	tokens = ft_calloc(wc + 2, sizeof(char *));
	while (i < wc)
	{
		tokens[i] = ft_strtok(input, delimiter);
		i++;
	}
	tokens[wc] = "EOFToken";
	tokens[wc + 1] = NULL;
	return (tokens);
}

void	lexer(char *input)
{
	char	**tokens;
	int		i;

	i = 0;
	if (input[0] == '\0')
		return ;
	tokens = ft_tokenize(input, ' ');
	print_list(tokens);
	parser();
}
