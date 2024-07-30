/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 21:12:47 by nnagel           ###   ########.fr       */
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

static char	*ft_getenv(char **envp, char *var)
{
	while (ft_strncmp(*envp, var, ft_strlen(var)))
		envp++;
	return (*envp);
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
			handle_pipe(&envp, tokens);
		else if (ft_strcomp(tokens[0], "echo"))
		{
			if (ft_strcomp(tokens[1], "-n"))
				ret = print_echo(tokens, 2);
			else
				ret = print_echo(tokens, 1);
		}
		else if (ft_strcomp(tokens[0], "env") && ft_strcomp(tokens[1], "EOFToken"))
			print_envp(envp);
		else if (ft_strcomp(tokens[0], "pwd") && ft_strcomp(tokens[1], "EOFToken"))
			ft_printf("%s\n", ft_getenv(envp, "PWD"));
		else if (ft_strcomp(tokens[0], "exit"))
		{
			if (ft_strcomp(tokens[1], "EOFToken"))
				exit(ret);
			else if (str_is_num(tokens[1]))
				exit(ft_atoi(tokens[1]));
		}
		else if (ft_strcomp(tokens[0], "cd"))
			ret = cd(&envp, tokens[1]);
		else if (ft_strcomp(tokens[0], "unset"))
			ret = unset(&envp, tokens);
		else if (ft_strcomp(tokens[0], "export"))
			ret = export(&envp, tokens);
		free_tokens(tokens);
	}
}

static char **copy_array(char **arr)
{
	int	i;
	char	**new;

	i = 0;
	new = malloc((array_size(arr) + 1) * sizeof(char *));
	while (arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	main(int argc, char **argv, char **envp)
{
	char	**envs;

	envs = copy_array(envp);
	if (argc >= 2)
		return (1);
	(void)argv;
	ft_main(envs);
	return (0);
}
