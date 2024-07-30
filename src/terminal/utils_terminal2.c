/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_terminal2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:17:24 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 15:35:28 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* static char	*format_dir_host(char *host, char *pwd)
{
	char	*hostname;
	char	*pwd_name;
	char	*curr_pwd;
	char	**process;
	char	*res;
	char	*temp;

	process = ft_split(host, '.');
	hostname = ft_strdup(process[0]);
	free_array(process);
	curr_pwd = ft_strdup(ft_strrchr(pwd, '/') + 1);
	if (ft_strchr(curr_pwd, '\n'))
		pwd_name = ft_substr(curr_pwd, 0, strlen(curr_pwd) - 1);
	else
		pwd_name = ft_strdup(curr_pwd);
	free_if_not_null(&curr_pwd);
	res = ft_strjoin(hostname, ":");
	free_if_not_null(&hostname);
	temp = ft_strjoin(res, pwd_name);
	free(res);
	res = temp;
	free_if_not_null(&pwd_name);
	return (res);
} */
static char	*get_formatted_hostname(char *host)
{
	char	**process;
	char	*hostname;

	process = ft_split(host, '.');
	hostname = ft_strdup(process[0]);
	free_array(process);
	return (hostname);
}

static char	*get_formatted_pwd(char *pwd)
{
	char	*curr_pwd;
	char	*pwd_name;

	curr_pwd = ft_strdup(ft_strrchr(pwd, '/') + 1);
	if (ft_strchr(curr_pwd, '\n'))
		pwd_name = ft_substr(curr_pwd, 0, strlen(curr_pwd) - 1);
	else
		pwd_name = ft_strdup(curr_pwd);
	free_if_not_null(&curr_pwd);
	return (pwd_name);
}

static char	*format_dir_host(char *host, char *pwd)
{
	char	*hostname;
	char	*pwd_name;
	char	*result;
	char	*final_result;

	pwd_name = get_formatted_pwd(pwd);
	hostname = get_formatted_hostname(host);
	result = ft_strjoin(hostname, ":");
	final_result = ft_strjoin(result, pwd_name);
	free_if_not_null(&hostname);
	free_if_not_null(&result);
	free_if_not_null(&pwd_name);
	return (final_result);
}

char	*get_formated(char *user, char *host, char *pwd)
{
	char	*dir_host;
	char	*res;
	char	*temp;

	dir_host = format_dir_host(host, pwd);
	temp = ft_strjoin(dir_host, " ");
	free(dir_host);
	res = temp;
	temp = ft_strjoin(res, user);
	free(res);
	res = temp;
	temp = ft_strjoin(res, "$ ");
	free(res);
	res = temp;
	return (res);
}

void	init_hostname(t_host *hostname, const char *str)
{
	hostname->argumt_cmd = malloc(sizeof(char *) * 2);
	if (!hostname->argumt_cmd)
	{
		perror("Error: malloc failed for cmd_args");
		exit(EXIT_FAILURE);
	}
	hostname->argumt_cmd[0] = ft_strdup(str);
	if (!hostname->argumt_cmd[0])
	{
		free(hostname->argumt_cmd);
		perror("Error: strdup failed for cmd_args[0]");
		exit(EXIT_FAILURE);
	}
	hostname->argumt_cmd[1] = NULL;
	hostname->result = malloc(sizeof(char) * BUFFER_SIZE);
	if (!hostname->result)
	{
		free(hostname->argumt_cmd[0]);
		free(hostname->argumt_cmd);
		perror("Error: malloc failed for res");
		exit(EXIT_FAILURE);
	}
}
