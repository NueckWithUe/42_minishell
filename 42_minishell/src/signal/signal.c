/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 08:16:02 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/10 00:46:22 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * handle_termios - Modifies the terminal settings 
 * to disable the echoing of control characters ctr+ C, D, Z...
 */

int	terminal_ctrl_proces(void)
{
	int				cur_status;
	struct termios	terminal;
	struct termios	org_terminal;

	cur_status = tcgetattr(STDIN_FILENO, &terminal);
	if (cur_status == -1)
	{
		ft_putstr_fd("failed tcgetattr\n", 2);
		return (1);
	}
	org_terminal = terminal;
	terminal.c_cflag &= ~(ECHOCTL);
	cur_status = tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	if (cur_status == -1)
	{
		ft_putstr_fd("failed tcsetattr\n", 2);
		tcsetattr(STDIN_FILENO, TCSANOW, &org_terminal);
		return (1);
	}
	return (0);
}

/**
 * Handles the SIGINT signal (Ctrl+C).
*/

void	sigint_process(int signal)
{
	char	*tmp;

	(void)signal;
	tmp = ft_strjoin(rl_line_buffer, " ");
	if (tmp == NULL)
	{
		ft_putstr_fd("Error: Failed to allocate memory\n", STDERR_FILENO);
		return ;
	}
	rl_replace_line(tmp, 0);
	free(tmp);
	rl_redisplay();
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * Signal handler for the SIGQUIT signal ctrl+\.
 */

void	sigquit_process(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit: 3", 1);
	ft_putstr('\n', 1);
}

/**
 * Configures signal handlers for the program start.
 */

void	start_signal_handler(t_minishell_struct *mini_data)
{
	(void)mini_data;
	if (signal(SIGINT, sigint_process) == SIG_ERR)
	{
		perror("Failed to set SIGINT handler");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("Failed to ignore SIGQUIT");
		exit(EXIT_FAILURE);
	}
}

/**
 * Configures signal handlers for the program stop.
 */

void	stop_signal_handler(t_minishell_struct *mini_data)
{
	(void)mini_data;
	if (signal(SIGINT, sigquit_process) == SIG_ERR)
	{
		perror("Failed to set SIGINT handler");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, sigquit_process) == SIG_ERR)
	{
		perror("Failed to ignore SIGQUIT");
		exit(EXIT_FAILURE);
	}
}
