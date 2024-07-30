/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 07:36:45 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 13:36:34 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*read_pipe_output(FILE *pipe)
{
	char	buffer[128];
	char	*result;
	size_t	result_len;
	size_t	buffer_len;
	char	*temp;

	result = NULL;
	result_len = 0;
	while (fgets(buffer, sizeof(buffer), pipe) != NULL)
	{
		buffer_len = ft_strlen(buffer);
		temp = realloc(result, result_len + buffer_len + 1);
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		result = temp;
		strcpy(result + result_len, buffer);
		result_len += buffer_len;
	}
	if (result && result[result_len - 1] == '\n')
		result[result_len - 1] = '\0';
	return (result);
}

char	*execute_command(const char *cmd)
{
	FILE	*pipe;
	char	*result;

	pipe = popen(cmd, "r");
	if (!pipe)
		return (NULL);
	result = read_pipe_output(pipe);
	pclose(pipe);
	return (result);
}

char	*get_name_of_term_formated(char *envp[])
{
	char	*username;
	char	*hostname;
	char	*pwd;
	char	*formatted_name;

	username = gett_env_value(envp, "USER");
	hostname = execute_command("/bin/hostname");
	pwd = execute_command("/bin/pwd");
	if (!username || !hostname || !pwd)
	{
		free(username);
		free(hostname);
		free(pwd);
		return (strdup("minishell$ "));
	}
	formatted_name = get_formated(username, hostname, pwd);
	free(username);
	free(hostname);
	free(pwd);
	return (formatted_name);
}

void	init_mini_variables(t_minishell_struct *mini, char *envp[])
{
	(void)envp;
	mini->cd_quite = 0;
	mini->fd_output = STDOUT_FILENO;
	mini->fd_input = STDIN_FILENO;
	mini->pwd = find_pwd_in_getcwd();
	mini->home = locate_home_getcwd();
	if (DEBUG)
	{
		ft_printf_2d(mini->envp, "ENVIRONMENT VARIABLES");
		mini->name_of_term = get_name_of_term_formated(mini->envp);
	}
	else
		mini->name_of_term = ft_strdup("minishell-0.1$ ");
}

void	init_minishell(t_minishell_struct *mini, char *envp[])
{
	int	len;

	len = verify_envp_len(envp);
	initialiaz_envp(envp, len, mini);
	init_mini_variables(mini, envp);
}
