/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:13:03 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/21 13:29:54 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

/*
	- Create double tab for pipes
		there are num_cmds-1 pipes => malloc(sizeof(int *) * (shell->num_cmds - 1))
	- Create all necessary pipes
		every pipe need two fd => malloc(sizeof(int) * 2);
*/

void	init_pipes(t_shell *shell)
{
	int	i;

	shell->pipes = malloc(sizeof(int *) * (shell->num_cmds - 1));
	if (!shell->pipes)
	{
		free_all(shell);
		ft_error("Error allocating memory for pipes\n");
	}
	i = 0;
	while (i < shell->num_cmds - 1)
	{
		shell->pipes[i] = malloc(sizeof(int) * 2);
		if (!shell->pipes[i])
		{
			free_all(shell);
			ft_error("Error allocating memory for pipe\n");
		}
		if (pipe(shell->pipes[i]) == -1)
		{
			free_all(shell);
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

/*
	- Call redirect pipes function
	- Checkif I have the path for the command
	- Execute the command
*/

void	call_execve(t_shell *shell, int index)
{
	redirect_pipes(shell, index);
	if (shell->path[index] == NULL)
	{
		free_all(shell);
		ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	execve(shell->path[index], shell->cmds[index].args, shell->env);
}

/*
	Parent process need to wait that all child are finished
*/

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

/*
	all pipes needs to be close because they are useless in parrent process
*/

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

/*
	- Create a child process for every command
	- Then execute each cmd on each child
*/

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
		if (pid == 0)
		{
			call_execve(shell, i);
			exit(127);
		}
		i++;
	}
	ft_close_pipes(shell);
	ft_wait_childs(shell);
}

void	execute_simple_cmd(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error("Error with fork");
	if (pid == 0)
	{
		execve(shell->path[0], shell->cmds[0].args, shell->env);
		exit(127);
	}
	else
		wait(&shell->exit_status);
}

void	execute_command(t_shell *shell)
{
	if (shell->num_cmds > 1)
		execute_pipe(shell);
	else
		execute_simple_cmd(shell);
}
