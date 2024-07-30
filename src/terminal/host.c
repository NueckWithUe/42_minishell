/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:08:51 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 15:24:22 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* void	get_hostname_child_process(t_host *t_hostname)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		handle_error("Pipe error");
	pid = fork();
	if (pid == -1)
		handle_error("Fork error");
	else if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			handle_error("dup2 error");
		close(pipefd[1]);
		if (execve(t_hostname->argumt_cmd[0],
				t_hostname->argumt_cmd, NULL) == -1)
			handle_error("execve error");
	}
	else
	{
		close(pipefd[1]);
		wait(NULL);
		if (read(pipefd[0], t_hostname->result, BUFFER_SIZE) == -1)
			handle_error("read error");
		close(pipefd[0]);
	}
} */

char	*gett_env_value(char *envp[], const char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = strlen(key);
	while (envp[i])
	{
		if (strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			return (strdup(envp[i] + key_len + 1));
		}
		i++;
	}
	return (NULL);
}

static void	child_process(t_host *t_hostname, int pipe_write_end)
{
	close(pipe_write_end - 1);
	if (dup2(pipe_write_end, STDOUT_FILENO) == -1)
		handle_error("dup2 error");
	close(pipe_write_end);
	if (execve(t_hostname->argumt_cmd[0], t_hostname->argumt_cmd, NULL) == -1)
		handle_error("execve error");
}

static void	handle_parent_process(int pipe_read_end, char *result)
{
	close(pipe_read_end + 1);
	wait(NULL);
	if (read(pipe_read_end, result, BUFFER_SIZE) == -1)
		handle_error("read error");
	close(pipe_read_end);
}

void	get_hostname_child_process(t_host *t_hostname)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		handle_error("Pipe error");
	pid = fork();
	if (pid == -1)
		handle_error("Fork error");
	else if (pid == 0)
	{
		child_process(t_hostname, pipefd[1]);
	}
	else
	{
		handle_parent_process(pipefd[0], t_hostname->result);
	}
}
