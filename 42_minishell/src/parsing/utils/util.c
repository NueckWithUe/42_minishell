/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 03:35:35 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/13 18:50:00 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	init_lexer_data(t_lexer_struct *lexer_dto, char *line)
{
	lexer_dto->line = ft_strdup(line);
	lexer_dto->position = 0;
	lexer_dto->dbl_quote = 0;
	lexer_dto->spl_quote = 0;
}

void	ft_printf_2d(char *str[], char *str_msg)
{
	int	i;

	i = 0;
	printf("\n%s\n", str_msg);
	while (str[i])
	{
		printf("%p [%d] ----- %s\n", (str + i), i, str[i]);
		i++;
	}
}

/* void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
} */


/* size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s[c] != '\0')
		c++;
	return (c);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
} */

int	my_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str && str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strncat(char *s1, const char *s2, int n)
{
	char	*res;
	int		i;
	int		j;
	int		s1_len;

	i = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	res = (char *)malloc((s1_len + n + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (j < n && s2 && s2[j] != '\0')
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free_if_not_null(s1);
	return (res);
}
