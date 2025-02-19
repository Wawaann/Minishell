/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:13:03 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/19 18:08:44 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

// void	execute_pipe(t_shell *shell)
// {

// }

void	execute_simple_cmd(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("Error with fork");
	if (pid == 0)
	{
		execve(shell->path[0], shell->cmds[0], shell->env);
		exit(127);
	}
	else
		wait(&shell->exit_status);
}

void	execute_command(t_shell *shell)
{
	/*if (shell->num_cmds > 1) // presence d'au moins un pipe
		execute_pipe(shell);
	else
		execute_simple_cmd(shell);*/
	execute_simple_cmd(shell);
}
