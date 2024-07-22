/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/22 21:14:46 by nnagel           ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	char	*input;
	char	**tokens;
	int		stop = 0;

	ret = 0;
	input = NULL;
	if (argc >= 2)
		return (1);
	(void)argv;
	while (!stop)
	{
		input = readline(">> ");
		tokens = lexer(input);
		if (ft_strchr(input, '|'))
			handle_pipe(tokens);
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
		else if (ft_strcomp(tokens[0], "exit") && ft_strcomp(tokens[1], "EOFToken"))
			exit(ret);
		else if (ft_strcomp(tokens[0], "cd"))
			ret = cd(&envp, tokens[1]);
		else if (ft_strcomp(tokens[0], "unset"))
			ret = unset(&envp, tokens);
		free_tokens(tokens);
	}
	return (ret);
}
