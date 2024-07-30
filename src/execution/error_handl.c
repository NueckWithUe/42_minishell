/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 07:51:03 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 15:51:40 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error_msg(char *message, int c, t_minishell_struct *mini)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	if (c == 1)
	{
		ft_putendl_fd(": command not found", STDERR_FILENO);
		mini->cd_quite = 127;
	}
	else if (c == 2)
	{
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		mini->cd_quite = 1;
	}
	else if (c == 3)
	{
		ft_putendl_fd(": not enough arguments", STDERR_FILENO);
		mini->cd_quite = 1;
	}
	else if (c == 4)
	{
		ft_putendl_fd(": HOME not set", STDERR_FILENO);
		mini->cd_quite = 1;
	}
}

void	error_print_message(char *message1, char *message2, int c,
		t_minishell_struct *mini)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message1, 2);
	if (message2 != NULL)
		ft_putstr_fd(message2, 2);
	if (c == 1)
	{
		ft_putendl_fd(": numeric argument required", 2);
		free_mini(mini);
		exit(255);
	}
	else if (c == 2)
	{
		ft_putendl_fd(": too many arguments", 2);
		mini->cd_quite = 1;
	}
	else if (c == 3)
	{
		ft_putendl_fd(": OLDPWD not set", 2);
		mini->cd_quite = 1;
	}
	else if (c == 4)
	{
		ft_putendl_fd(": HOME not set", 2);
		mini->cd_quite = 1;
	}
}

static int	**initialize_fd_array(int lst_size)
{
	int	**fds;
	int	i;

	fds = malloc(lst_size * sizeof(int *));
	if (!fds)
		stop("malloc fd");
	i = 0;
	while (i < lst_size)
	{
		fds[i] = malloc(2 * sizeof(int));
		if (!fds[i])
			stop("malloc fd[i]");
		i++;
	}
	return (fds);
}

static void	configure_pipes(int **fds, int lst_size)
{
	int	i;

	i = 0;
	while (i < lst_size)
	{
		if (pipe(fds[i]) < 0)
			stop("Pipe");
		i++;
	}
}

int	**set_fd(t_minishell_struct *mini, int lst_size, int flag)
{
	mini->fds = initialize_fd_array(lst_size);
	if (flag)
		configure_pipes(mini->fds, lst_size);
	else
	{
		mini->fds[0][0] = dup(STDIN_FILENO);
		mini->fds[0][1] = dup(STDOUT_FILENO);
		mini->fds[1][0] = mini->commands->fd_infile;
		mini->fds[1][1] = mini->commands->fd_outfile;
	}
	return (mini->fds);
}
