/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 06:43:56 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/13 09:26:24 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_if_not_null(char *str)
{
	if (str != NULL)
		free(str);
	str = NULL;
}

void	free_list_of_token(t_token_struct *token)
{
	t_token_struct	*tmp;
	t_token_struct	*next;

	if (!token)
		return ;
	tmp = token;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	token = NULL;
}

void	free_ast(t_asset *ast)
{
	t_asset	*cur;
	t_asset	*next;
	int		i;

	cur = ast;
	while (cur)
	{
		next = cur->next;
		if (cur->args)
		{
			i = 0;
			while (cur->args[i])
			{
				free(cur->args[i]);
				i++;
			}
			free(cur->args);
		}
		free(cur);
		cur = next;
	}
}

void	print_t_ast(t_asset *command, char *str_msg)
{
	if (!command)
		printf("The command is NULL\n");
	while (command)
	{
		printf("Arguments:\n");
		if (command->args)
			ft_printf_2d(command->args, str_msg);
		else
			printf("  args: NULL\n");
		printf("fd_infile: %d\n", command->fd_infile);
		printf("fd_outfile: %d\n", command->fd_outfile);
		printf("Next command: %p\n", (void *)command->next);
		printf("Previous command: %p\n", (void *)command->prev);
		command = command->next;
	}
}

void	free_arg(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return ;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}