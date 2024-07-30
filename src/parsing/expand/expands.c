/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:18:48 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/26 04:06:40 by blatifat         ###   ########.fr       */
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

	i = 0;
	if (!args[i] || !args[*position])
		return ;
	free_if_not_null(&args[*position]);
	i = *position;
	if (args[i])
		free_if_not_null(&args[i]);
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

char	*expansion_status(t_minishell_struct *mini,
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
			if (!double_quotes(mini, args, &i, expand))
				return (NULL);
		}
		else if (args[i] == '$' && args[i + 1] != '\0')
		{
			if (handle_expansion(mini, args, &i, expand))
				*read_fl = 1;
		}
		else
		{
			if (!append_char(expand, args[i]))
				return (NULL);
			i++;
		}
	}
	return (*expand);
}

int	check_expansion(t_minishell_struct *mini, char **args,
	int *read_fl)
{
	char	*local_expand;
	char	*arg;

	local_expand = NULL;
	arg = *args;
	if (expansion_status(mini, arg, &local_expand, read_fl))
	{
		free_if_not_null(&arg);
		*args = local_expand;
		return (1);
	}
	if (local_expand)
		free(local_expand);
	return (1);
}

static void	handle_expansion_process(t_minishell_struct *mini,
	t_asset *cmd, int *flag_rf) {
	int		i;
	char	**new_args;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (!check_expansion(mini, &cmd->args[i], flag_rf))
		{
			shift_elmt(cmd->args, &i);
		}
		if (*flag_rf)
		{
			new_args = arry_concat(cmd->args,
					ft_split(cmd->args[i], ' '), i, flag_rf);
			if (!new_args)
			{
				free_array(cmd->args);
				return ;
			}
			cmd->args = new_args;
		}
		i++;
	}
}

int	passed_expasion(t_minishell_struct *mini)
{
	t_asset	*tem_commands;
	int		flag_rf;

	tem_commands = mini->commands;
	flag_rf = 0;
	while (tem_commands)
	{
		if (DEBUG)
			ft_printf_2d(tem_commands->args, "before expansion");
		printf("Processing command: \n");
		handle_expansion_process(mini, tem_commands, &flag_rf);
		if (DEBUG)
			ft_printf_2d(tem_commands->args, "after expansion");
		printf("Expansion finished for command.\n");
		tem_commands = tem_commands->next;
	}
	return (1);
}
