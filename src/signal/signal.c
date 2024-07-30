/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 08:16:02 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 14:02:37 by blatifat         ###   ########.fr       */
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
		perror("tcgetattr failed");
		return (1);
	}
	org_terminal = terminal;
	terminal.c_lflag &= ~(ECHOCTL);
	cur_status = tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	if (cur_status == -1)
	{
		perror("tcsetattr failed");
		tcsetattr(STDIN_FILENO, TCSANOW, &org_terminal);
		return (1);
	}
	return (0);
}

void	sigquit_handler(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}
// Handles the SIGINT signal (Ctrl+C)

static void	sigint_handler(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// Handles the SIGQUIT signal (Ctrl+\)

/**
 * Configures signal handlers for the program start.
 */

void	start_signal_handler(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
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

void	stop_signal_handler(void )
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		perror("Failed to set SIGINT handler");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		perror("Failed to ignore SIGQUIT");
		exit(EXIT_FAILURE);
	}
}
