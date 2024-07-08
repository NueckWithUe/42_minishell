/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:36:24 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/06 03:20:53 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_strcomp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

static int	ft_get_index(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcomp(tokens[i], "|"))
			return (i + 1);
		i++;
	}
	return (0);
}

static int	ft_size_before_pipe(char **arr)
{
	int	i;

	i = 0;
	while (!ft_strcomp(arr[i], "|"))
	{
		i++;
	}
	return (i);
}

static int	ft_size_after_pipe(char **arr)
{
	int	i;
	int	j;

	i = ft_size_before_pipe(arr) + 1;
	j = 0;
	while (!ft_strcomp(arr[i], "EOFToken"))
	{
		i++;
		j++;
	}
	return (j);
}

void	handle_pipe(char **tokens)
{
	int		pipefd[2];
	pid_t	pid;
	char	buffer[128];
	char	**foreground_pipe;
	char	**background_pipe;
	int		i;
	int		j;
	int		index_after_pipe;
	// char	*output

	foreground_pipe = malloc(sizeof(char *) * ft_size_before_pipe(tokens) + 1);
	background_pipe = malloc(sizeof(char *) * ft_size_after_pipe(tokens) + 1);
	i = 0;
	while (!ft_strcomp(tokens[i], "|"))
	{
		foreground_pipe[i] = ft_strdup(tokens[i]);
		i++;
	}
	foreground_pipe[i] = NULL;
	i++;
	j = 0;
	while (!ft_strcomp(tokens[i], "EOFToken"))
	{
		background_pipe[j] = ft_strdup(tokens[i]);
		i++;
		j++;
	}
	background_pipe[j + 1] = NULL;
	index_after_pipe = ft_get_index(tokens);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid > 0) //Parent process
	{
		close(pipefd[0]); //gets closed because it's the reading side of the pipe and therefore unused
		ft_printf("Executing command before pipe...\n");
		if (ft_strcomp(tokens[0], "ls"))
			execve("/bin/ls", foreground_pipe, NULL);
		if (ft_strcomp(tokens[0], "echo"))
			execve("/bin/echo", foreground_pipe, NULL);
		close(pipefd[1]);
		wait(NULL);
	}
	else //Child process
	{
		close(pipefd[1]); //gets closed because it's the writing side of the pipe and therefore unused
		read(pipefd[0], buffer, sizeof(buffer));
		// output from before pipe = command
		ft_printf("Executing command after pipe...\n");
		if (ft_strcomp(tokens[index_after_pipe], "ls"))
			execve("/bin/ls", background_pipe, NULL);
		if (ft_strcomp(tokens[index_after_pipe], "echo"))
			execve("/bin/echo", background_pipe, NULL);
		close(pipefd[0]);
		exit(EXIT_SUCCESS);
	}
}
