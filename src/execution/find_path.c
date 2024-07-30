/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 08:17:42 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 15:55:48 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_trim_path(char *path)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (path[i] != '\0' && path[i] != '=')
		i++;
	if (path[i] == '\0')
		return (ft_strdup(path));
	temp = malloc((ft_strlen(path) - i));
	if (!temp)
	{
		perror("ft_trim_path: malloc failed");
		return (NULL);
	}
	j = 0;
	i++;
	while (path[i] != '\0')
		temp[j++] = path[i++];
	temp[j] = '\0';
	free_if_not_null(&path);
	return (temp);
}

static	char	*check_paths(char **path_2d, char *command)
{
	int		i;
	char	*path_s;
	char	*trimmed_path;

	i = 0;
	path_s = NULL;
	trimmed_path = NULL;
	while (path_2d[i])
	{
		trimmed_path = ft_trim_path(path_2d[i]);
		path_s = ft_strjoin(trimmed_path, command);
		free_if_not_null(&trimmed_path);
		if (access(path_s, F_OK | X_OK) == 0)
		{
			free_if_not_null(&command);
			free_array(path_2d);
			return (path_s);
		}
		free_if_not_null(&path_s);
		i++;
	}
	return (NULL);
}

char	*ft_find_path(t_minishell_struct *mini, char *arg, int i)
{
	char	*command;
	char	*path_s;
	char	**path_2d;

	(void)i;
	if (arg[0] == '/')
		return (init_string(mini, arg));
	if (arg[0] == '.' && arg[1] == '/' && arg[2] != '\0')
		return (init_path(mini, arg));
	path_s = ft_getenv(mini, "PATH");
	if (!path_s)
		return (free_if_not_null(&arg),
			print_error_msg(mini->commands->args[0], 2, mini), NULL);
	path_2d = ft_split(path_s, ':');
	free_if_not_null(&path_s);
	if (!path_2d || !path_2d[0])
		return (free_array(path_2d), free_if_not_null(&arg), NULL);
	command = ft_strjoin("/", arg);
	path_s = check_paths(path_2d, command);
	if (path_s)
		return (path_s);
	free_if_not_null(&command);
	free_array(path_2d);
	return (arg);
}

static char	*construct_full_path(const char *cwd, const char *s)
{
	char	*result;
	char	*temp_input_path;
	int		i;

	i = 0;
	temp_input_path = malloc(ft_strlen(s));
	if (!temp_input_path)
		return (NULL);
	while (s[++i] != '\0')
		temp_input_path[i - 1] = s[i];
	temp_input_path[i - 1] = '\0';
	result = ft_strjoin(cwd, temp_input_path);
	free(temp_input_path);
	return (result);
}

char	*init_path(t_minishell_struct *mini, char *s)
{
	char	*cwd;
	char	*result;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (print_error_msg(mini->commands->args[0], 2, mini),
			free_if_not_null(&s), NULL);
	result = construct_full_path(cwd, s);
	free(cwd);
	if (!result)
		return (print_error_msg(mini->commands->args[0], 2, mini),
			free_if_not_null(&s), NULL);
	if (access(result, F_OK | X_OK) == 0)
		return (free_if_not_null(&s), result);
	print_error_msg(mini->commands->args[0], 2, mini);
	free_if_not_null(&s);
	return (free(result), NULL);
}
