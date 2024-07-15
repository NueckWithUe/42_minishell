/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:36:24 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/15 13:04:40 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
	{
		ft_printf("Array is NULL\n");
		return ;
	}
	while (arr[i])
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}

static int	ft_strcomp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

static int	size_before_pipe(char **tokens, int a)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (!ft_strcomp(tokens[i], "|"))
		i++;
	if (a)
	{
		i++;
		while (!ft_strcomp(tokens[i], "EOFToken"))
		{
			i++;
			j++;
		}
		return (j);
	}
	return (i);
}

static void	get_command(char **tokens, char ***com1, char ***com2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	com1[0] = (char **)malloc(sizeof(char *) * size_before_pipe(tokens, 0) + 1);
	com2[0] = (char **)malloc(sizeof(char *) * size_before_pipe(tokens, 1) + 1);
	while (!ft_strcomp(tokens[i], "|"))
	{
		com1[0][i] = ft_strdup(tokens[i]);
		i++;
	}
	com1[0][i] = NULL;
	com1[1] = NULL;
	i++;
	while (!ft_strcomp(tokens[i], "EOFToken"))
	{
		com2[0][j] = ft_strdup(tokens[i]);
		i++;
		j++;
	}
	com2[0][j] = NULL;
	com2[1] = NULL;
}

void	handle_pipe(char **tokens)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	char	*argv1[] = {"/bin/ls", "-l", NULL};
	char	*argv2[] = {"/usr/bin/wc", "-l", NULL};

	char **test1;
	char **test2;
	get_command(tokens, &test1, &test2);
	print_arr(test1);
	print_arr(test2);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve("/bin/ls", argv1, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		execve("/usr/bin/wc", argv2, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
