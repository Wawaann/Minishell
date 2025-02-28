/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:56:42 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/28 11:03:39 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

pid_t	g_sig_pid;

void	duplicate_env(t_shell *shell, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	shell->env = malloc(sizeof(char *) * (i + 1));
	if (!shell->env)
		return ;
	i = 0;
	while (env[i])
	{
		shell->env[i] = ft_strdup(env[i]);
		i++;
	}
	shell->env[i] = NULL;
}

void	init_shell(t_shell *shell, char **env)
{
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->path = NULL;
	shell->pipes = NULL;
	shell->num_cmds = 0;
	duplicate_env(shell, env);
	shell->exit_status = 0;
	g_sig_pid = 0;
	init_signals();
}

// void	display_shell(t_shell *shell)
// {
// 	printf("input: %s\n", shell->input);
// 	printf("tokens: ");
// 	for (int i = 0; shell->tokens[i]; i++)
// 		printf("[%s] ", shell->tokens[i]);
// 	printf("\n");
// 	printf("num_cmds: %d\n", shell->num_cmds);
// 	printf("cmds:\n");
// 	for (int i = 0; i < shell->num_cmds; i++)
// 	{
// 		printf("cmd %d:\n", i);
// 		printf("args: ");
// 		for (int j = 0; shell->cmds[i].args[j]; j++)
// 			printf("[%s] ", shell->cmds[i].args[j]);
// 		printf("\n");
// 		printf("in_count: %d\n", shell->cmds[i].in_count);
// 		printf("in: ");
// 		for (int j = 0; j < shell->cmds[i].in_count; j++)
// 			printf("[%d: %s] ", shell->cmds[i].in[j].type,
// 				shell->cmds[i].in[j].file);
// 		printf("\n");
// 		printf("out_count: %d\n", shell->cmds[i].out_count);
// 		printf("out: ");
// 		for (int j = 0; j < shell->cmds[i].out_count; j++)
// 			printf("[%d: %s] ", shell->cmds[i].out[j].type,
// 				shell->cmds[i].out[j].file);
// 		printf("\n");
// 	}
// }

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)av;
	if (ac != 1)
		return (0);
	init_shell(&shell, env);
	while (1)
	{
		shell.input = readline("$> ");
		if (!shell.input || ft_strncmp(shell.input, "exit", 4) == 0)
			break ;
		add_history(shell.input);
		shell.tokens = tokenize(shell.input, &shell.num_cmds);
		if (check_error(&shell))
		{
			shell.cmds = get_commands(shell.tokens, shell.num_cmds);
			init_path(&shell);
			init_pipes(&shell);
			execute_command(&shell);
		}
		free_shell(&shell);
	}
	free_tokens(shell.env);
	free_shell(&shell);
	clear_history();
	return (0);
}
