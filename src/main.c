/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:47:56 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/25 14:44:27 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	creation_cmds_dur(t_shell *shell)
{
	// Allouer un tableau de 3 commandes + 1 NULL pour marquer la fin
	shell->num_cmds = 2;
	shell->cmds = malloc(sizeof(t_command) * (shell->num_cmds));

	// Commande 1: `ls -l`
	shell->cmds[0].args = malloc(sizeof(char *) * 3);
	shell->cmds[0].args[0] = ft_strdup("cat");
	shell->cmds[0].args[1] = ft_strdup("-e");
	shell->cmds[0].args[2] = NULL;

	//shell->cmds[0].in = NULL;
	shell->cmds[0].count_in = 1;
	shell->cmds[0].in = malloc(sizeof(t_redirection) * 2);
	shell->cmds[0].in[0].file = ft_strdup("toto");
	shell->cmds[0].in[0].type = 2;
	// shell->cmds[0].in[1].file = ft_strdup("file1.txt");
	// shell->cmds[0].in[1].type = 1;

	//shell->cmds[0].out = NULL;
	shell->cmds[0].count_out = 1;
	shell->cmds[0].out = ft_calloc(2, sizeof(t_redirection));
	shell->cmds[0].out[0].file = ft_strdup("outfile2.txt");
	shell->cmds[0].out[0].type = 3;
	// shell->cmds[0].out[1].file = ft_strdup("outfile2.txt");
	// shell->cmds[0].out[1].type = 3;
	// shell->cmds[0].out[2].file = ft_strdup("file3.txt");
	// shell->cmds[0].out[2].type = 3;

	// =====================================================

	// Commande 2: `grep e`
	shell->cmds[1].args = malloc(sizeof(char *) * 3);
	shell->cmds[1].args[0] = ft_strdup("grep");
	shell->cmds[1].args[1] = ft_strdup("e");
	shell->cmds[1].args[2] = NULL;

	//shell->cmds[1].in = NULL;
	shell->cmds[1].count_in = 1;
	shell->cmds[1].in = malloc(sizeof(t_redirection) * 1);
	shell->cmds[1].in[0].file = ft_strdup("outfile2.txt");
	shell->cmds[1].in[0].type = 1;

	shell->cmds[1].out = NULL;
	shell->cmds[1].count_out = 0;
	// shell->cmds[1].out = malloc(sizeof(t_redirection));
	// shell->cmds[1].out->file = ft_strdup("outfile.txt");
	// shell->cmds[1].out->type = 3;

	// =====================================================

	// Commande 3: `wc -l`
	// shell->cmds[2].args = malloc(sizeof(char *) * 3);
	// shell->cmds[2].args[0] = ft_strdup("wc");
	// shell->cmds[2].args[1] = ft_strdup("-l");
	// shell->cmds[2].args[2] = NULL;
	// shell->cmds[2].in = NULL;
	// shell->cmds[2].count_in = 0;
	// shell->cmds[2].out = NULL;
	// shell->cmds[2].count_out = 0;
	// shell->cmds[2].out = malloc(sizeof(t_redirection));
	// shell->cmds[2].out->file = ft_strdup("outfile.txt");
	// shell->cmds[2].out->type = 3;
}

void	init_shell(t_shell *shell, char **env)
{
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->num_cmds = 0;
	shell->env = env;
	shell->exit_status = 0;
	shell->hd_fd[0] = -2;
	shell->hd_fd[1] = -2;
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

		creation_cmds_dur(&shell);
		init_path(&shell);
		init_pipes(&shell);

		execute_command(&shell);

		free_all(&shell);
		free(shell.input);
	}
	clear_history();
	return (0);
}
