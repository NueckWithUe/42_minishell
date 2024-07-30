/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_terminal3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:20:46 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/26 04:44:30 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verify_envp_len(char *envp[])
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
		i++;
	return (i);
}

char	*construct_home_path(char **path_segments)
{
	char	*tmp;
	char	*home;

	if (!path_segments[0] || !path_segments[1])
	{
		free_array(path_segments);
		return (ft_strdup(""));
	}
	tmp = ft_strjoin("/", path_segments[0]);
	home = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = home;
	home = ft_strjoin(tmp, path_segments[1]);
	free(tmp);
	free_array(path_segments);
	if (!home)
		return (ft_strdup(""));
	return (home);
}

char	*locate_home_getcwd(void)
{
	char	*pwd;
	char	**path_segments;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("Error: getcwd failed");
		return (ft_strdup(""));
	}
	path_segments = ft_split(pwd, '/');
	free(pwd);
	home = construct_home_path(path_segments);
	return (home);
}

char	*find_pwd_in_getcwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("Error: getcwd failed");
		return (ft_strdup(""));
	}
	return (pwd);
}

char	*construct_parts(char *hostname, char *pwd_name, char *user)
{
	char	*res;
	char	*temp;

	res = ft_strjoin(hostname, ":");
	free_if_not_null(&hostname);
	temp = ft_strjoin(res, pwd_name);
	free_if_not_null(&res);
	res = temp;
	temp = ft_strjoin(res, " ");
	free_if_not_null(&res);
	res = temp;
	temp = ft_strjoin(res, user);
	free_if_not_null(&res);
	res = temp;
	temp = ft_strjoin(res, "$ ");
	free_if_not_null(&res);
	res = temp;
	return (res);
}
