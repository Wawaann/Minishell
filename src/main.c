/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:47:56 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/25 15:34:51 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

// void	creation_cmds_dur(t_shell *shell)
// {
// 	// Allouer un tableau de 3 commandes + 1 NULL pour marquer la fin
// 	shell->num_cmds = 3;
// 	shell->cmds = malloc(sizeof(t_command) * (shell->num_cmds));

// 	// Commande 1: `ls -l`
// 	shell->cmds[0].args = malloc(sizeof(char *) * 3);
// 	shell->cmds[0].args[0] = ft_strdup("cat");
// 	shell->cmds[0].args[1] = ft_strdup("-e");
// 	shell->cmds[0].args[2] = NULL;
// 	shell->cmds[0].in = NULL;
// 	// shell->cmds[0].in = malloc(sizeof(t_redirection));
// 	// shell->cmds[0].in->file = ft_strdup("infile.txt");
// 	// shell->cmds[0].in->type = 1;
// 	shell->cmds[0].out = NULL;
// 	// shell->cmds[0].out = malloc(sizeof(t_redirection));
// 	// shell->cmds[0].out->file = ft_strdup("outfile.txt");
// 	// shell->cmds[0].out->type = 4;

// 	// Commande 2: `grep e`
// 	shell->cmds[1].args = malloc(sizeof(char *) * 3);
// 	shell->cmds[1].args[0] = ft_strdup("grep");
// 	shell->cmds[1].args[1] = ft_strdup("e");
// 	shell->cmds[1].args[2] = NULL;
// 	shell->cmds[1].in = NULL;
// 	//shell->cmds[1].out = NULL;
// 	shell->cmds[1].out = malloc(sizeof(t_redirection));
// 	shell->cmds[1].out->file = ft_strdup("outfile.txt");
// 	shell->cmds[1].out->type = 3;

// 	// Commande 3: `wc -l`
// 	shell->cmds[2].args = malloc(sizeof(char *) * 3);
// 	shell->cmds[2].args[0] = ft_strdup("wc");
// 	shell->cmds[2].args[1] = ft_strdup("-w");
// 	shell->cmds[2].args[2] = NULL;
// 	shell->cmds[2].in = NULL;
// 	shell->cmds[2].out = NULL;
// 	// shell->cmds[2].out = malloc(sizeof(t_redirection));
// 	// shell->cmds[2].out->file = ft_strdup("outfile.txt");
// 	// shell->cmds[2].out->type = 3;
// }

void	init_shell(t_shell *shell, char **env)
{
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->num_cmds = 0;
	shell->env = env;
	shell->exit_status = 0;
}

void	display_shell(t_shell *shell)
{
	printf("input: %s\n", shell->input);
	printf("tokens: ");
	for (int i = 0; shell->tokens[i]; i++)
		printf("[%s] ", shell->tokens[i]);
	printf("\n");
	printf("num_cmds: %d\n", shell->num_cmds);
	printf("cmds:\n");
	for (int i = 0; i < shell->num_cmds; i++)
	{
		printf("cmd %d:\n", i);
		printf("args: ");
		for (int j = 0; shell->cmds[i].args[j]; j++)
			printf("[%s] ", shell->cmds[i].args[j]);
		printf("\n");
		printf("in_count: %d\n", shell->cmds[i].in_count);
		printf("in: ");
		for (int j = 0; j < shell->cmds[i].in_count; j++)
			printf("[%d: %s] ", shell->cmds[i].in[j].type,
				shell->cmds[i].in[j].file);
		printf("\n");
		printf("out_count: %d\n", shell->cmds[i].out_count);
		printf("out: ");
		for (int j = 0; j < shell->cmds[i].out_count; j++)
			printf("[%d: %s] ", shell->cmds[i].out[j].type,
				shell->cmds[i].out[j].file);
		printf("\n");
	}
}

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
		shell.cmds = get_commands(shell.tokens, shell.num_cmds);
		display_shell(&shell);

		init_path(&shell);
		init_pipes(&shell);

		execute_command(&shell);

		free_shell(&shell);
	}
	clear_history();
	return (0);
}
