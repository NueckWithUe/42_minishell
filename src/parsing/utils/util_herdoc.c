/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 02:06:14 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/25 02:29:15 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	write_herdoc(int fd, char *seperator, t_minishell_struct *mini, int j)
{
	char	*line;

	(void)mini;
	(void)j;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, seperator, ft_strlen(seperator)) == 0)
		{
			free_if_not_null(&line);
			break ;
		}
		check_expansion(mini, &line, &j);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free_if_not_null(&line);
	}
	if (close(fd) == -1)
	{
		ft_putstr_fd("minishell : No such file or directory\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

void	push_at_front(char **args, int *postion, int n)
{
	int	j;
	int	i;
	int	k;

	j = 0;
	while (args[j])
		j++;
	if (*postion < 0 || *postion >= j || n < 0 || *postion + n > j)
		return ;
	k = *postion;
	while (k < *postion + n)
		free_if_not_null(&args[k++]);
	i = *postion;
	while (i < j - n)
	{
		args[i] = args[i + n];
		i++;
	}
	while (i < j)
		args[i++] = NULL;
	(*postion)--;
}

int	check_file_access(const char *filename, t_minishell_struct *mini)
{
	if (verify_file_access(filename) == 0)
	{
		mini->cd_quite = 1;
		return (0);
	}
	if (check_file_type(filename) == 0)
	{
		mini->cd_quite = 126;
		return (0);
	}
	return (1);
}

int	handle_ouput_red(t_asset *beg_cmd, int *i)
{
	if (ft_strchr(beg_cmd->args[*i], '>') && ft_strlen(beg_cmd->args[*i]) <= 2)
	{
		if (!write_append_to_file(beg_cmd, i))
			return (0);
	}
	return (1);
}

int	handle_input_red(t_asset *beg_cmd, t_minishell_struct *mini, int *i)
{
	if (ft_strchr(beg_cmd->args[*i], '<') && ft_strlen(beg_cmd->args[*i]) <= 2)
	{
		if (!process_heredoc_from_file(beg_cmd, mini, i))
			return (0);
	}
	return (1);
}
