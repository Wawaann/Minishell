/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:47:56 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/19 15:41:34 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->input = NULL;
    shell->tokens = NULL;
    shell->cmds = NULL;
    shell->num_cmds = 0;
    shell->env = env;  // Copie de l'environnement
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
			break;
		add_history(shell.input);
		printf("input: %s\n", shell.input);
		free(shell.input);
	}
	rl_clear_history();
	return (0);
}
