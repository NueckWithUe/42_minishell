/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:23:52 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/25 02:34:09 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	handle_env_var(t_minishell_struct *mini,
	const char *arg, int *i, char **expand)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*new_expand;

	start = *i;
	while (arg[*i] && (isalnum(arg[*i]) || arg[*i] == '_'))
		(*i)++;
	var_name = strndup(arg + start, *i - start);
	var_value = get_env_value(mini->envp, var_name);
	free(var_name);
	if (var_value)
	{
		new_expand = ft_strncat(*expand, var_value, strlen(var_value));
		free(var_value);
		if (new_expand)
		{
			*expand = new_expand;
			return (1);
		}
	}
	return (0);
}

int	check_exit_status(int status_val, int *i, char **expand)
{
	char	*exit_status;
	char	*new_expand;
	int		res;

	exit_status = NULL;
	new_expand = NULL;
	res = 0;
	(*i)++;
	exit_status = ft_itoa(status_val);
	if (!exit_status)
		return (0);
	new_expand = ft_strncat(*expand, exit_status, ft_strlen(exit_status));
	if (new_expand)
	{
		*expand = new_expand;
		res = 1;
	}
	free_if_not_null(&exit_status);
	if (!res)
		(*i)--;
	return (res);
}

int	handle_expansin_char(t_minishell_struct *mini,
	char next_char, int *i, char **expand) {
	if (next_char == '?')
	{
		if (!check_exit_status(mini->cd_quite, i, expand))
			return (0);
	}
	else if (next_char == '$')
	{
		if (!check_exit_status(95394, i, expand))
			return (0);
	}
	return (1);
}

int	handle_expansion(t_minishell_struct *mini, const char *arg,
	int *i, char **expand)
{
	char	next_char;

	(*i)++;
	next_char = arg[*i];
	if (next_char == '?' || next_char == '$')
	{
		if (!handle_expansin_char(mini, next_char, i, expand))
			return (0);
	}
	else
	{
		if (!handle_env_var(mini, arg, i, expand))
		{
			(*i)--;
			return (0);
		}
	}
	return (1);
}
