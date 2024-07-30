/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:36:13 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 22:54:49 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*get_saned_path(char *path)
{
	char	*saned_path;
	int		i;
	int		j;

	saned_path = malloc(ft_strlen(path) + 1);
	if (!saned_path)
		return (NULL);
	i = 1;
	j = 0;
	while (path[i])
	{
		saned_path[j] = path[i];
		i++;
		j++;
	}
	saned_path[j] = '\0';
	return (saned_path);
}

static void	set_pwd(char ***envp, char *buffer)
{
	int	i;

	i = 0;
	while (ft_strncmp((*envp)[i], "PWD", 3))
		i++;
	(*envp)[i] = ft_strjoin("PWD=", buffer);
}

static void	set_oldpwd(char ***envp, char *oldpwd)
{
	int	i;

	i = 0;
	while (ft_strncmp((*envp)[i], "OLDPWD", 6))
		i++;
	(*envp)[i] = ft_strjoin("OLDPWD=", oldpwd);
}

// static char	*ft_getenv(char **envp, char *var)
// {
// 	while (ft_strncmp(*envp, var, ft_strlen(var)))
// 		envp++;
// 	return (*envp);
// }

static char	*ft_getoldpwd(char **envp, char *var)
{
	while (ft_strncmp(*envp, var, ft_strlen(var)))
		envp++;
	return (*envp + 4);
}

int	cd(char ***envp, char *path)
{
	char	*alt_path;
	char	*saned_path;
	char	*oldpwd;
	char	*buffer = malloc(sizeof(char) * 1024);

	oldpwd = ft_getoldpwd(*envp, "PWD");
	ft_printf("%s\n", oldpwd);
	if (ft_strcomp(path, "-"))
		alt_path = ft_strdup(oldpwd);
	else if (ft_strcomp(path, "EOFToken"))
		alt_path = ft_strdup(getenv("HOME"));
	else if (path[0] == '~')
	{
		if (path[1] == '\0')
			alt_path = ft_strdup(getenv("HOME"));
		else
		{
			saned_path = get_saned_path(path);
			alt_path = ft_strjoin(getenv("HOME"), saned_path);
			free(saned_path);
		}
	}
	else
		alt_path = ft_strdup(path);
	if (chdir(alt_path) == -1)
	{
		ft_printf("Error.\nDirectory '%s' not found.\n", alt_path);
		free(alt_path);
		return (1);
	}
	getcwd(buffer, 1024);
	set_pwd(envp, buffer);
	set_oldpwd(envp, oldpwd);
	free(buffer);
	free(alt_path);
	return (0);
}

/* that's how you change PWD in envp */

// int main(int argc, char **argv, char **envp)
// {

// 	if (argc != 2)
// 		return (1);
// 	int i;
// 	i = 0;
// 	while (ft_strncmp(envp[i], "PWD", 3))
// 		i++;
// 	printf("oldpwd: %s\n", getenv("PWD"));
// 	chdir(argv[1]);
// 	char *pwd;
// 	pwd = getcwd(pwd, 1024);
// 	envp[i] = ft_strjoin("PWD=", pwd);
// 	printf("pwd: %s\n", getenv("PWD"));
// }