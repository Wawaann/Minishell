/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:13:03 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/20 11:01:14 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	init_pipes(t_shell *shell)
{
	int	i;

	shell->pipes = malloc(sizeof(int *) * (shell->num_cmds - 1));
	if (!shell->pipes)
	{
		// Free allocated memory
		ft_error("Error allocating memory for pipes\n");
	}
	i = 0;
	while (i < shell->num_cmds - 1)
	{
		shell->pipes[i] = malloc(sizeof(int) * 2);
		if (!shell->pipes[i])
		{
			// Free allocated memory
			ft_error("Error allocating memory for pipe\n");
		}
		if (pipe(shell->pipes[i]) == -1)
		{
			// Free allocated memory
			ft_error("Pipe error\n");
		}
		i++;
	}
}

/*
	first command (index == 0)
		-> redirect stdout into next pipe
	last command
		-> redirect stdin into prev pipe
	middle command
		-> redirect stdin into prev pipe
		-> redirect stdout into next pipe

	Close all the unuse pipes
	Dup2 copies the pipes and redirects these copies.
	You therefore need to close all the original pipes (those before the copy)
	to avoid blocking.
*/

void	redirect_pipes(t_shell *shell, int index)
{
	int i;

	if (index == 0)
		dup2(shell->pipes[index][1], STDOUT_FILENO);
	else if (index == shell->num_cmds - 1)
		dup2(shell->pipes[index - 1][0], STDIN_FILENO);
	else
	{
		dup2(shell->pipes[index - 1][0], STDIN_FILENO);
		dup2(shell->pipes[index][1], STDOUT_FILENO);
	}

	i = 0;
	while (i < shell->num_cmds - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

void	call_execve(t_shell *shell, int index)
{
	redirect_pipes(shell, index);
	if (shell->path[index] == NULL)
	{
		// Free allocated memory here
		ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	execve(shell->path[index], shell->cmds[index], shell->env);
}

void	ft_wait_childs(t_shell *shell)
{
	int		i;

	i = 0;
	while (i < shell->num_cmds)
	{
		wait(&shell->exit_status);
		i++;
	}
}

void	ft_close_pipes(t_shell *shell)
{
	int		i;

	i = 0;
	while (i < shell->num_cmds - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

void	execute_pipe(t_shell *shell)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < shell->num_cmds)
	{
		pid = fork();
		if (pid == -1)
			ft_error("Error with fork");
		else if (pid == 0)
		{
			call_execve(shell, i);
			exit(127);
		}
		i++;
	}
}

void	execute_simple_cmd(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
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
	if (shell->num_cmds > 1) // One pipe at least
	{
		execute_pipe(shell);
	}
	else
		execute_simple_cmd(shell);
}
