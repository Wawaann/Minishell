/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:56:42 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/28 16:48:06 by ebigotte         ###   ########.fr       */
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

void	minishell(t_shell *shell, char **env)
{
	char	*prompt;

	init_shell(shell, env);
	while (1)
	{
		prompt = get_prompt(shell->env);
		shell->input = readline(prompt);
		if (!shell->input)
			break ;
		add_history(shell->input);
		shell->tokens = tokenize(shell->input, &shell->num_cmds);
		if (check_error(shell))
		{
			shell->cmds = get_commands(shell->tokens, shell->num_cmds);
			display_shell(shell);
			init_path(shell);
			init_pipes(shell);
			execute_command(shell);
		}
		free_shell(shell);
		free(prompt);
	}
	if (prompt)
		free(prompt);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)av;
	if (ac != 1)
		return (0);
	minishell(&shell, env);
	free_tokens(shell.env);
	free_shell(&shell);
	clear_history();
	return (0);
}
