/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:41:47 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/27 04:12:30 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * Handles content within single quotes in the input string.
 * Copies the content between single quotes to 
 * the expansion string and updates the index.
 */

char	*single_quotes_handler(const char *args, int *i, char **expand)
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

int	append_char(char **expand, char c)
{
	size_t	len;
	char	*new_expand;

	if (!expand || !*expand)
		return (0);
	len = ft_strlen(*expand);
	new_expand = malloc(len + 2);
	if (!new_expand)
		return (0);
	strcpy(new_expand, *expand);
	new_expand[len] = c;
	new_expand[len + 1] = '\0';
	free(*expand);
	*expand = new_expand;
	return (1);
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

char	*double_quotes(t_minishell_struct *mini,
	const char *args, int *i, char **expand)
{
	int	org_idx;

	(*i)++;
	while (args[*i] && args[*i] != '\"')
	{
		if (args[*i] == '$' && special_char(args[*i + 1]))
		{
			org_idx = *i;
			if (!handle_expansion(mini, args, i, expand))
			{
				*i = org_idx;
				return (NULL);
			}
		}
		else
		{
			if (!append_char(expand, args[*i]))
				return (NULL);
			(*i)++;
		}
	}
	if (args[*i] == '\"')
		(*i)++;
	return (*expand);
}
