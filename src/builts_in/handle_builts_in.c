/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builts_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:11 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/04 11:48:43 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

static int	handle_parent_only_builtin(t_shell *shell, int i)
{
	char	*cmd;

	cmd = shell->cmds[i].args[0];
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(shell, i), 1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(shell, shell->cmds[i].args), 1);
	if (ft_strcmp(cmd, "export") == 0 && shell->cmds[i].args[1])
		return (ft_export(shell, shell->cmds[i].args), 1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(shell, shell->cmds[i].args[1]), 1);
	return (0);
}

int	handle_builtin(t_shell *shell, int i, int is_child)
{
	char	*cmd;

	if (!shell->cmds[i].args[0])
		return (0);
	cmd = shell->cmds[i].args[0];
	if (!is_child && handle_parent_only_builtin(shell, i))
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(shell, shell->cmds[i].args, shell->cmds[i].echo);
	else if (ft_strcmp(cmd, "export") == 0 && !shell->cmds[i].args[1])
		print_export(shell);
	else
		return (0);
	return (1);
}
