/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 03:35:35 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/26 06:25:51 by blatifat         ###   ########.fr       */
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
	s1_len = strlen(s1);
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
	free_if_not_null(&s1);
	return (res);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
