/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_herdoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 01:33:09 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 14:32:21 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	handle_herdoc(int fd, char *seprator, t_minishell_struct *mini, int j)
{
	fd = open("obj/herdoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_putstr_fd("minishell : No such file or directory\n",
				STDERR_FILENO), -1);
	if (write_herdoc(fd, seprator, mini, j) == -1)
		return (-1);
	fd = open("obj/herdoc", O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("minishell : No such file or directory\n",
				STDERR_FILENO), -1);
	return (fd);
}

int	process_heredoc_from_file(t_asset *beg_cmd,
	t_minishell_struct *mini, int *i)
{
	int		j;
	char	*file_name;

	j = 0;
	file_name = *(beg_cmd->args + *i + 1);
	if (check_file_access(file_name, mini) == 0)
		return (0);
	if (beg_cmd->fd_infile != STDIN_FILENO)
		close(beg_cmd->fd_infile);
	if (ft_strncmp(*(beg_cmd->args + *i), "<", 2) == 0)
		beg_cmd->fd_infile = open(file_name, O_RDONLY);
	else if (ft_strncmp(*(beg_cmd->args + *i), "<<", 2) == 0)
		beg_cmd->fd_infile = handle_herdoc(beg_cmd->fd_infile,
				file_name, mini, j);
	if (beg_cmd->fd_infile == -1)
	{
		ft_putstr_fd("minishell : No such file or directory\n", STDERR_FILENO);
		mini->cd_quite = 1;
		return (0);
	}
	push_at_front(beg_cmd->args, i, 2);
	return (1);
}

int	write_append_to_file(t_asset *beg_cmd, int *i)
{
	int	flags;

	flags = 0;
	if (beg_cmd->fd_outfile != STDOUT_FILENO)
		close(beg_cmd->fd_outfile);
	if (ft_strncmp(*(beg_cmd->args + *i), ">", 2) == 0)
		flags = O_CREAT | O_RDWR | O_TRUNC;
	else if (ft_strncmp(*(beg_cmd->args + *i), ">>", 2) == 0)
		flags = O_CREAT | O_RDWR | O_APPEND;
	else
	{
		ft_putstr_fd("Invalid redirection operator\n", STDERR_FILENO);
		return (0);
	}
	beg_cmd->fd_outfile = open(*(beg_cmd->args + *i + 1), flags, 0644);
	if (beg_cmd->fd_outfile == -1)
	{
		ft_putstr_fd("minishell : No such file or directory\n", STDERR_FILENO);
		return (0);
	}
	push_at_front(beg_cmd->args, i, 2);
	return (1);
}

/**
 *Processes input, output, append, and here-document redirections for commands.
 */

int	handle_redirection_input(t_minishell_struct *mini)
{
	int		i;
	t_asset	*beg_cmd;

	beg_cmd = mini->commands;
	while (beg_cmd)
	{
		i = 0;
		while (beg_cmd->args && beg_cmd->args[i])
		{
			if (!handle_ouput_red(beg_cmd, &i)
				|| !handle_input_red(beg_cmd, mini, &i))
			{
				mini->cd_quite = 1;
				return (0);
			}
			else
				i++;
		}
		beg_cmd = beg_cmd->next;
	}
	return (1);
}
