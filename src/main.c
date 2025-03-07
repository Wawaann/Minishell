/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:56:42 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/07 17:09:34 by ebigotte         ###   ########.fr       */
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

void	exec(t_shell *shell)
{
	shell->cmds = get_commands(shell->tokens, shell->num_cmds);
	init_path(shell);
	init_pipes(shell);
	execute_command(shell);
}

void	minishell(t_shell *shell, char **env)
{
	init_shell(shell, env);
	while (1)
	{
		shell->prompt = get_prompt(shell->env);
		shell->input = readline(shell->prompt);
		if (!shell->input)
			break ;
		if (shell->input[0] != '\0')
		{
			add_history(shell->input);
			tokenize(shell);
			if (check_error(shell))
				exec(shell);
		}
		free_shell(shell, false, false);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)av;
	if (ac != 1)
		return (0);
	minishell(&shell, env);
	free_shell(&shell, true, true);
	return (0);
}
