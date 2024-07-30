/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:49:47 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/26 04:05:38 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_ok_parsing(t_minishell_struct *mini)
{
	if (!is_lexically_valid(mini))
		return (0);
	if (!validate_syntax(mini))
		return (0);
	if (!generat_asset_cmd_instruct(mini))
		return (0);
	if (!passed_expasion(mini))
		return (0);
	if (!handle_redirection_input(mini))
		return (0);
	return (1);
}
