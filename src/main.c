/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:47:56 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/21 13:29:23 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	creation_cmds_dur(t_shell *shell)
{
	// Allouer un tableau de 3 commandes + 1 NULL pour marquer la fin
	shell->num_cmds = 3;
	shell->cmds = malloc(sizeof(t_command) * (shell->num_cmds));

	// Commande 1: `ls -l`
	shell->cmds[0].args = malloc(sizeof(char *) * 3);
	shell->cmds[0].args[0] = ft_strdup("ls");
	shell->cmds[0].args[1] = ft_strdup("-l");
	shell->cmds[0].args[2] = NULL;
	shell->cmds[0].in = NULL;
	shell->cmds[0].out = NULL;

	// Commande 2: `grep e`
	shell->cmds[1].args = malloc(sizeof(char *) * 3);
	shell->cmds[1].args[0] = ft_strdup("grep");
	shell->cmds[1].args[1] = ft_strdup("e");
	shell->cmds[1].args[2] = NULL;
	shell->cmds[1].in = NULL;
	shell->cmds[1].out = NULL;

	// Commande 3: `wc -l`
	shell->cmds[2].args = malloc(sizeof(char *) * 3);
	shell->cmds[2].args[0] = ft_strdup("wc");
	shell->cmds[2].args[1] = ft_strdup("-l");
	shell->cmds[2].args[2] = NULL;
	shell->cmds[2].in = NULL;
	shell->cmds[2].out = NULL;
}

void	init_shell(t_shell *shell, char **env)
{
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->num_cmds = 0;
	shell->env = env;
	shell->exit_status = 0;
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
