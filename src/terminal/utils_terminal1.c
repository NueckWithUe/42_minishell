/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_terminal1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 04:53:31 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/23 22:57:50 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_beg_with_str(char *envp[], const char *str)
{
	size_t	str_len;
	int		i;

	if (!envp || !str)
		return (0);
	str_len = ft_strlen(str);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], str, str_len) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*equal_value(const char *env)
{
	if (!env)
		return (NULL);
	while (*env && *env != '=')
		env++;
	if (*env == '=')
		env++;
	return (ft_strdup(env));
}

int	correct_value(const char *str)
{
	int	i;
	int	flag;

	flag = 0;
	if (!str)
		return (-1);
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			flag = (1);
		if (ft_isalpha(str[i]))
		{
			flag = 2;
			break ;
		}
		i++;
	}
	return (flag);
}

int	getenv_set(char **envp, char *to_get)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && strncmp(envp[i], to_get, strlen(to_get)) != 0)
		i++;
	if (envp[i] == NULL)
		return (0);
	return (1);
}

char	*ft_getenv(t_minishell_struct *mini, char *to_get)
{
	char	*env;
	int		i;

	i = 0;
	while (mini->envp[i] != NULL && ft_strncmp(mini->envp[i], to_get,
			ft_strlen(to_get)) != 0)
		i++;
	if (mini->envp[i] == NULL)
		return (NULL);
	env = ft_strdup(mini->envp[i]);
	return (env);
}
