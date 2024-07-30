/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/23 02:32:29 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
	tokens = NULL;
}

static int	str_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	**copy_env(char **envp)
{
	int		i;
	char	**own_envs;

	i = 0;
	own_envs = malloc(sizeof(char *) * array_size(envp) * 1);
	while (envp[i])
	{
		own_envs[i] = ft_strdup(envp[i]);
		i++;
	}
	return (own_envs);
}

static void	ft_main(char **envp)
{
	int		ret;
	char	*input;
	char	**tokens;

	ret = 0;
	input = NULL;
	while (1)
	{
		input = readline(">> ");
		tokens = lexer(input);
		if (ft_strchr(input, '|'))
			handle_pipe(envp, tokens);
		else if (ft_strcomp(tokens[0], "echo"))
		{
			if (ft_strcomp(tokens[1], "-n"))
				ret = print_echo(tokens, 2);
			else
				ret = print_echo(tokens, 1);
		}
		else if (ft_strcomp(tokens[0], "env") && ft_strcomp(tokens[1], "EOFToken"))
			ret = print_arr(envp);
		else if (ft_strcomp(tokens[0], "pwd") && ft_strcomp(tokens[1], "EOFToken"))
			ft_printf("%s\n", getenv("PWD"));
		else if (ft_strcomp(tokens[0], "exit"))
		{
			if (ft_strcomp(tokens[1], "EOFToken"))
				exit(ret);
			else if (str_is_num(tokens[1]))
				exit(ft_atoi(tokens[1]));
		}
		else if (ft_strcomp(tokens[0], "cd"))
			ret = cd(envp, tokens[1]);
		else if (ft_strcomp(tokens[0], "unset"))
			ret = unset(&envp, tokens);
		else if (ft_strcomp(tokens[0], "export"))
			ret = export(envp, tokens);
		free_tokens(tokens);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**envs;

	if (argc >= 2)
		return (1);
	(void)argv;
	envs = copy_env(envp);
	ft_main(envs);
	return (0);
}
