/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 02:25:25 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/26 04:48:00 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	locate_env_var(char **envp, const char *name, const char *new_value)
{
	int		i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(new_value);
			return ;
		}
		i++;
	}
}

int	check_envp(char **envp, const char *var)
{
	int		i;
	size_t	var_len;

	i = 0;
	if (!envp || !var)
		return (-1);
	var_len = ft_strlen(var);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], var, var_len) == 0
			&& (envp[i][var_len] == '='
			|| envp[i][var_len] == '\0'
			|| (envp[i][var_len] == '+' && envp[i][var_len + 1] == '=')))
			return (i);
		i++;
	}
	return (-1);
}

static void	add_env_var(t_minishell_struct *mini,
	int *idx, const char *var, const char *value)
{
	char	*combined_var;

	combined_var = ft_strjoin(var, value);
	if (!combined_var)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	mini->envp[*idx] = combined_var;
	(*idx)++;
}

static void	process_existing_envp(char *envp[],
	int *idx, t_minishell_struct *mini, int len)
{
	int	i;

	i = 0;
	while (envp[i] && *idx < len)
	{
		if (env_beg_with_str(envp, "OLDPWD=")
			&& strncmp(envp[i], "OLDPWD", 6) == 0)
		{
			free_if_not_null(&mini->envp[*idx]);
			mini->envp[*idx] = ft_strdup("OLDPWD");
		}
		else
		{
			mini->envp[*idx] = ft_strdup(envp[i]);
		}
		if (!mini->envp[*idx])
		{
			perror("Failed to allocate memory");
			exit(EXIT_FAILURE);
		}
		(*idx)++;
		i++;
	}
}

void	envp_preparation(char *envp[], int idx,
	t_minishell_struct *mini, int len)
{
	if (!envp || !mini || !mini->envp)
		return ;
	idx = 0;
	process_existing_envp(envp, &idx, mini, len);
	if (!check_envp(mini->envp, "PWD"))
		add_env_var(mini, &idx, "PWD=", getcwd(NULL, 0));
	if (!check_envp(mini->envp, "OLDPWD"))
		add_env_var(mini, &idx, "OLDPWD", "");
	if (!check_envp(mini->envp, "SHLVL"))
		add_env_var(mini, &idx, "SHLVL=", "1");
	else
		refresh_shell_level(mini, 1);
	mini->envp[idx] = NULL;
	printf("Set mini->envp[%d] to NULL\n", idx);
}
