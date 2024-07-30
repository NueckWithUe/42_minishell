/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:02:20 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 20:24:56 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	search_and_remove(char ***envp, char *to_remove)
{
	int	i;

	i = 0;
	while (ft_strncmp((*envp)[i], to_remove, ft_strlen(to_remove)))
		i++;
	//remove line from envp;
}

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

t_lst	*convert_env_to_list(char **envp)
{
	t_lst	*env_lst;
	int		i;

	env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		ft_insert_at_end(&env_lst, envp[i]);
		i++;
	}
	return (env_lst);
}
