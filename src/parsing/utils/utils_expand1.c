/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:36:37 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/25 02:28:49 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_env_value(char **envp, char *env_var)
{
	int	len;
	int	i;

	len = ft_strlen(env_var);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], env_var, len) == 0 && envp[i][len] == '=')
		{
			return (ft_strdup(envp[i] + len + 1));
		}
		i++;
	}
	return (NULL);
}

char	*extract_env_var(const char *arg, int *i)
{
	int		beg;
	char	*env_var;
	int		end;

	beg = *i;
	env_var = NULL;
	while (arg[*i] && envp_string_end_check(arg[*i]))
		(*i)++;
	end = *i;
	env_var = ft_substr(arg, beg, end - beg);
	return (env_var);
}
