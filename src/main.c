/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:47:56 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/20 11:19:27 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	creation_cmds_dur(t_shell *shell)
{
	// Allocation du tableau de commandes (2 commandes max)
	shell->cmds = malloc(sizeof(char **) * 3);

	// Première commande (ex: ["ls", "-l", NULL])
	shell->cmds[0] = malloc(sizeof(char *) * 3);
	shell->cmds[0][0] = ft_strdup("ls");
	shell->cmds[0][1] = ft_strdup("-l");
	shell->cmds[0][2] = NULL;

	shell->cmds[1] = malloc(sizeof(char *) * 3);
	shell->cmds[1][0] = ft_strdup("wc");
	shell->cmds[1][1] = ft_strdup("-w");
	shell->cmds[1][2] = NULL;

	// Fin du tableau de commandes
	shell->cmds[2] = NULL;
}

void	free_cmds(t_shell *shell)
{
	// Libération de la mémoire
	free(shell->cmds[0][0]);
	free(shell->cmds[0][1]);
	free(shell->cmds[0]);

	free(shell->cmds[1][0]);
	free(shell->cmds[1][1]);
	free(shell->cmds[1]);

	free(shell->cmds);
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
	creation_cmds_dur(&shell);
	shell.num_cmds = 2;
	init_path(&shell);
	while (1)
	{
		shell.input = readline("$> ");
		if (!shell.input || ft_strncmp(shell.input, "exit", 4) == 0)
			break;
		add_history(shell.input);
		//printf("input: %s\n", shell.input);
		init_pipes(&shell);
		execute_command(&shell);
		ft_close_pipes(&shell);
		ft_wait_childs(&shell);
		free(shell.input);
	}
	rl_clear_history();
	free_cmds(&shell);
	return (0);
}
