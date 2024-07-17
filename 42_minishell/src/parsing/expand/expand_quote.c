/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:41:47 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/13 18:28:58 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * Handles content within single quotes in the input string.
 * Copies the content between single quotes to 
 * the expansion string and updates the index.
 */

char	*single_quotes_handler(char *args, int *i, char **expand)
{
	int	beg;
	int	end;

	if (!args || !i || !expand)
		return (NULL);
	beg = ++(*i);
	if (args[*i] == '\'')
	{
		(*i)++;
		return (NULL);
	}
	while (args[*i] && args[*i] != '\'')
		(*i)++;
	end = *i;
	if (args[*i] != '\'')
		return (NULL);
	(*i)++;
	*expand = ft_strncat(*expand, (args + beg), (end - beg));
	return (*expand);
}

/**
 * append_char - Appends a single character to the end of a string.
 * Ensures the string is properly null-terminated after appending the character.
 */

void	append_char(char **expand, char c)
{
	size_t	len;

	len = ft_strlen(*expand);
	(*expand)[len] = c;
	(*expand)[len + 1] = '\0';
}

static int	special_char(char c)
{
	return (c != ' ' && c != '\"' && c != '\0');
}

/**
 * double_quotes - Handles content within double quotes in the input string.
 * Expands environment variables and appends characters between
 * double quotes to the expansion string.
 */


char	*double_quotes(t_minishell_struct *mini_data,
	char *args, int *i, char **expand)
{
	int	org_idx;

	(*i)++;
	while (args[*i] && args[*i] != '\"')
	{
		if (args[*i] == '$' && special_char(args[*i + 1]))
		{
			org_idx = *i;
			if (!execute_expansion(mini_data, args, i, expand))
			{
				*i = org_idx;
				return (NULL);
			}
		}
		else
		{
			append_char(expand, args[*i]);
			(*i)++;
		}
	}
	(*i)++;
	return (*expand);
}
