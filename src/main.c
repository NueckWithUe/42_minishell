/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/01 17:47:31 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv)
{
	char	*args[] = { "ls", "-l", "./", NULL };
	char	*env[] = { "HOME=/home/username", "PATH=/bin:/usr/bin", NULL };

	if (argc >= 2)
		return (1);
	if (execve("/bin/ls", args, env) == -1)
		perror("execve");
	ft_printf("argc: %d\nargv[0]: %s\n", argc, argv[0]);
	return (0);
}
