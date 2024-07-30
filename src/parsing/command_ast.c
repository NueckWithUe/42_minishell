/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 07:57:26 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/26 06:25:41 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * initialize_arguments - Initializes the arguments array for a 
 * command from a token list.Copies values from the tokens to the 
 * command's argument array based on the token type.
 */

int	initialize_arguments(t_token_struct **token, t_asset **start_cmd, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if ((*token)->type == WORD)
			(*start_cmd)->args[j] = ft_strdup((*token)->value);
		else if ((*token)->type == '<')
			(*start_cmd)->args[j] = ft_strdup("<");
		else if ((*token)->type == '>')
			(*start_cmd)->args[j] = ft_strdup(">");
		else if ((*token)->type == APP_OUT)
			(*start_cmd)->args[j] = ft_strdup(">>");
		else if ((*token)->type == HEAD_DOC)
			(*start_cmd)->args[j] = ft_strdup("<<");
		if (!(*start_cmd)->args[j])
			return (0);
		*token = (*token)->next;
		j++;
	}
	return (1);
}

/**
 * assign_cmd_arg - Assigns arguments to a command from a token list.
 * Allocates memory for the arguments array, initializes it with token 
 * values, and sets the last element to NULL.
 */

int	assign_cmd_arg(t_token_struct **token, t_asset **start_cmd)
{
	int		i;
	t_asset	*tmp;

	i = count_args(*token);
	tmp = *start_cmd;
	if (i == 0)
		return (1);
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmp->args)
		return (0);
	if (!initialize_arguments(token, &tmp, i))
		return (0);
	tmp->args[i] = NULL;
	if (DEBUG)
		ft_printf_2d(tmp->args, "ARGS After init");
	return (1);
}

/**
 * Inserts a new AST node at the end of the command list.
 */

int	insert_new_ast_node(t_token_struct **cur_token, t_asset **cur_ast)
{
	int		arg_count;
	t_asset	*new_node;

	new_node = (t_asset *)malloc(sizeof(t_asset));
	if (!new_node)
		return (0);
	arg_count = count_args(*cur_token);
	new_node->args = (char **)malloc((arg_count + 1) * sizeof(char *));
	if (!new_node->args)
		return (0);
	add_args(cur_token, new_node);
	new_node->next = NULL;
	new_node->fd_infile = 0;
	new_node->fd_outfile = 1;
	new_node->prev = *cur_ast;
	if (*cur_ast)
		(*cur_ast)->next = new_node;
	else
		*cur_ast = new_node;
	*cur_ast = new_node;
	printf("Inserted new AST node with %d arguments\n", arg_count);
	return (1);
}

/**
 * generat_asset_cmd_instruct - Generates an AST structure for  
 * commands from tokens.Iterates through the tokens and builds 
 * a command list (AST) in mini->commands.
 */

int	generat_asset_cmd_instruct(t_minishell_struct *mini)
{
	t_token_struct	*cur_token;
	t_asset			*cur_ast;

	if (!mini || !mini->token)
		return (0);
	cur_token = mini->token;
	cur_ast = NULL;
	while (cur_token && cur_token->type != EOL)
	{
		if (!token_process(&cur_token, &cur_ast))
			return (0);
	}
	mini->commands = cur_ast;
	if (DEBUG)
		print_t_asset(mini->commands, "--AFTER--");
	return (1);
}
