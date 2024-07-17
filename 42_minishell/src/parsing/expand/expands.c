/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:18:48 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/13 19:27:26 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/**
 * shift_elmt - Shifts elements in the array to the left from the given position.
 * Frees the element at the given position and updates the position index.
 */

static void	shift_elmt(char **args, int *position)
{
	int	i;

	if (!args[i] || !position || *position < 0)
		return ;
	i = *position;
	if (args[i])
		free_if_not_null(args[i]);
	while (args[i] != NULL)
	{
		args[i] = args[i + 1];
		i++;
	}
	(*position)--;
}

/**
 * expansion_status - Processes and expands the content of the input string.
 * Handles single and double quotes, environment variable expansions,
 * and updates the expanded result.
 */

char	*expansion_status(t_minishell_struct *mini_data,
	const char *args, char **expand, int *read_fl)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '\'')
			single_quotes_handler(args, &i, expand);
		else if (args[i] == '\"')
		{
			if (!double_quotes(mini_data, args, &i, expand))
				return (NULL);
		}
		else if (args[i] == '$' && args[i + 1] != '\0')
		{
			if (execute_expansion(mini_data, args, &i, expand))
				*read_fl = 1;
		}
		else
		{
			append_char(expand, args[i]);
			i++;
		}
	}
	return (*expand);
}

/**
 * check_expansion - Checks and performs the expansion of an argument.
 * If expansion is successful, updates the argument and frees the old value.
 */

int	check_expansion(t_minishell_struct *mini_data, char **args,
	char **expand, int *read_fl)
{
	char	*local_expand;
	char	*arg;

	local_expand = NULL;
	arg = *args;
	if (expansion_status(mini_data, arg, &local_expand, read_fl))
	{
		free_if_not_null(arg);
		*args = local_expand;
		return (1);
	}
	if (local_expand)
		free(local_expand);
	return (0);
}

static void	handle_expansion(t_minishell_struct *mini_dto,
		t_asset *cmd, int *flag_rf) {
	int		i;
	char	**new_args;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (!is_needed_expansion(mini_dto, &cmd->args[i], flag_rf))
			unshift_element(cmd->args, &i);
		if (*flag_rf)
		{
			*new_args = concat_arrays(cmd->args,
					ft_split(cmd->args[i], ' '), i, flag_rf);
			if (!new_args)
			{
				free_2d(cmd->args);
				return ;
			}
			cmd->args = new_args;
		}

		i++;
	}
}

int	passed_expasion(t_minishell_struct *mini_data)
{
	t_asset	*tem_cmds;
	int		flag_rf;

	tem_cmds = mini_data->commands;
	flag_rf = 0;

	while (tem_cmds)
	{
		if (DEBUG)
			ft_printf_2d(tem_cmds->args, "before expansion");
		handle_expansion(mini_data, tem_cmds, &flag_rf);
		if (DEBUG)
			ft_printf_2d(tem_cmds->args, "after expansion");
		tem_cmds = tem_cmds->next;
	}
	return (1);
}
