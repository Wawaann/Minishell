/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:13:03 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/04 14:26:40 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	call_execve(t_shell *shell, int index)
{
	redirect_heredoc(shell, index);
	redirect_pipes(shell, index);
	redirect_infiles(shell, index);
	redirect_outfiles(shell, index);
	if (handle_builtin(shell, index, 1))
		exit(shell->exit_status);
	if (shell->path[index] == NULL)
		exit(127);
	execve(shell->path[index], shell->cmds[index].args, shell->env);
}

void	execute_pipe(t_shell *shell)
{
	int		i;

	collect_all_heredocs(shell);
	i = 0;
	while (i < shell->num_cmds)
	{
		g_sig_pid = fork();
		if (g_sig_pid == -1)
			ft_error("Error with fork");
		if (g_sig_pid == 0)
		{
			call_execve(shell, i);
			exit(127);
		}
		if (i == shell->num_cmds - 1)
			shell->last_child = g_sig_pid;
		i++;
	}
	ft_close_pipes(shell);
	ft_wait_childs(shell);
	cleanup_heredocs(shell);
}

void	execute_simple_cmd(t_shell *shell)
{
	collect_all_heredocs(shell);
	if (shell->cmds[0].args[0] && is_parent_builtin(shell->cmds[0].args[0]))
	{
		handle_builtin(shell, 0, 0);
		return ;
	}
	g_sig_pid = fork();
	if (g_sig_pid == -1)
		ft_error("Error with fork");
	if (g_sig_pid == 0)
	{
		redirect_simple_cmd(shell);
		if (handle_builtin(shell, 0, 1))
			exit(shell->exit_status);
		if (shell->path[0] == NULL)
		{
			ft_putstr_fd(" command not found\n", 2);
			exit(127);
		}
		execve(shell->path[0], shell->cmds[0].args, shell->env);
		exit(127);
	}
	ft_wait(shell);
	cleanup_heredocs(shell);
}

void	execute_command(t_shell *shell)
{
	if (shell->num_cmds > 1)
		execute_pipe(shell);
	else
		execute_simple_cmd(shell);
}
