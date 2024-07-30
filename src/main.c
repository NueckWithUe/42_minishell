/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 22:07:16 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_global_signal;

g_global_signal = 0;
/* int	main(int argc, char **argv)
{
	char	        *ret;
    t_lexer_struct lexer_data = {NULL, 0, 0, 0};
    t_token_struct *token;

	ret = NULL;
	if (argc >= 2)
		return (1);
	(void)argv;
	ret = readline(">> ");
	lexer_data.line = ret;
	token = extract_token_word(&lexer_data);
	if (token->type != ERROR)
	{
		printf("Token: Type = %d, Value = %s\n", token->type, token->value);
	}
	else
	{
		printf("Error: unmatched quotes\n");
	}
	return (0);
} */

/* int main(int argc, char **argv) {
    char *ret;
    t_lexer_struct lexer_data = {NULL, 0, 0, 0};
    t_token_struct *token;

    ret = NULL;
    if (argc >= 2)
        return (1);
    (void)argv;
    ret = readline(">> ");
    lexer_data.line = ret;

    while (lexer_data.position < (int)strlen(lexer_data.line)) {
        token = next_token(&lexer_data);
        if (token->type == EOL) break;
        if (token->type != ERROR) {
            printf("Token: Type = %d, Value = %s\n", token->type, token->value);
        } else {
            printf("Error: unmatched quotes\n");
            break;
        }
        // Libérer la mémoire du token après utilisation pour éviter les fuites de mémoire
        free(token->value);
        free(token);
    }

    free(ret);
    return (0);
}
 */

/* int main(int argc, char **argv) {
    char *ret;
    t_lexer_struct lexer_data = {NULL, 0, 0, 0};
    t_token_struct *token;

    ret = NULL;
    if (argc >= 2)
        return 1;

    (void)argv;
    ret = readline(">> ");
    lexer_data.line = ret;
    token = extract_token_word(&lexer_data);

    if (token->type != ERROR) {
        printf("Token: Type = %d, Value = %s\n", token->type, token->value);
    } else {
        printf("Error: unmatched quotes\n");
    }

    // Test de l'expansion avec des arguments prédéfinis
    char *envp[] = {"USER=user1", "PATH=/usr/bin", "HOME=/home/user1", NULL};
    char *args[] = {ret, NULL};
    t_asset cmd = {NULL, NULL, args, 0, 0};
    t_minishell_struct mini_data = {NULL, NULL, NULL, NULL, NULL, envp, NULL, 0, 0, 0, NULL, &cmd, NULL};

    printf("Before expansion:\n");
    for (int i = 0; cmd.args[i]; i++) {
        printf("%s ", cmd.args[i]);
    }
    printf("\n");

    passed_expasion(&mini_data);

    printf("After expansion:\n");
    for (int i = 0; cmd.args[i]; i++) {
        printf("%s ", cmd.args[i]);
    }
    printf("\n");

    return 0;
} */

/* nnagel current main */
/*
#include "../include/minishell.h"

static void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
	tokens = NULL;
}

static int	str_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	*ft_getenv(char **envp, char *var)
{
	while (ft_strncmp(*envp, var, ft_strlen(var)))
		envp++;
	return (*envp);
}

static void	ft_main(char **envp)
{
	int		ret;
	char	*input;
	char	**tokens;

	ret = 0;
	input = NULL;
	while (1)
	{
		input = readline(">> ");
		tokens = lexer(input);
		if (ft_strchr(input, '|'))
			handle_pipe(&envp, tokens);
		else if (ft_strcomp(tokens[0], "echo"))
		{
			if (ft_strcomp(tokens[1], "-n"))
				ret = print_echo(tokens, 2);
			else
				ret = print_echo(tokens, 1);
		}
		else if (ft_strcomp(tokens[0], "env") && ft_strcomp(tokens[1], "EOFToken"))
			print_envp(envp);
		else if (ft_strcomp(tokens[0], "pwd") && ft_strcomp(tokens[1], "EOFToken"))
			ft_printf("%s\n", ft_getenv(envp, "PWD"));
		else if (ft_strcomp(tokens[0], "exit"))
		{
			if (ft_strcomp(tokens[1], "EOFToken"))
				exit(ret);
			else if (str_is_num(tokens[1]))
				exit(ft_atoi(tokens[1]));
		}
		else if (ft_strcomp(tokens[0], "cd"))
			ret = cd(&envp, tokens[1]);
		else if (ft_strcomp(tokens[0], "unset"))
			ret = unset(&envp, tokens);
		else if (ft_strcomp(tokens[0], "export"))
			ret = export(&envp, tokens);
		free_tokens(tokens);
	}
}

static char **copy_array(char **arr)
{
	int	i;
	char	**new;

	i = 0;
	new = malloc((array_size(arr) + 1) * sizeof(char *));
	while (arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	main(int argc, char **argv, char **envp)
{
	char	**envs;

	envs = copy_array(envp);
	if (argc >= 2)
		return (1);
	(void)argv;
	ft_main(envs);
	return (0);
}

*/

/* int	main(int argc, char *argv[], char *envp[])
{
	t_minishell_struct	mini_data;
	int					quite;

	(void)argv;
	if (argc != 1 || !*envp)
	{
		return (1);
	}
	stop_signal_handler();
	init_minishell(&mini_data, envp);

	rl_bind_key('\t', rl_complete);
	using_history();

	terminal_initializ(&mini_data);

	clear_history();

	quite = mini_data.cd_quite;
	printf("exit\n");

	return (quite);
}
 */
