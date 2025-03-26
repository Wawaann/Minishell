/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:41:27 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/10 13:54:02 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	init_pipes(t_shell *shell)
{
	int	i;

	shell->pipes = ft_calloc(shell->num_cmds - 1, sizeof(int *));
	if (!shell->pipes)
	{
		free_shell(shell, false, false);
		ft_error("Error allocating memory for pipes\n");
	}
	i = 0;
	while (i < shell->num_cmds - 1)
	{
		shell->pipes[i] = malloc(sizeof(int) * 2);
		if (!shell->pipes[i])
		{
			free_shell(shell, false, false);
			ft_error("Error allocating memory for pipe\n");
		}
		if (pipe(shell->pipes[i]) == -1)
		{
			free_shell(shell, false, false);
			ft_error("Pipe error\n");
		}
		i++;
	}
}

void	redirect_pipes(t_shell *shell, int index)
{
	int	i;

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

void	ft_wait_childs(t_shell *shell)
{
	int		i;
	int		status;
	int		final_status;
	pid_t	pid;

	i = 0;
	while (i < shell->num_cmds)
	{
		pid = wait(&status);
		if (pid == shell->last_child)
			final_status = status;
		i++;
	}
	shell->exit_status = WEXITSTATUS(final_status);
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
