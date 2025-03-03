/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builts_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:11 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/03 12:37:58 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

int	handle_builtin(t_shell *shell, int i, int is_child)
{
	char	*cmd;

	if (!shell->cmds[i].args[0])
		return (0);
	cmd = shell->cmds[i].args[0];
	if (!is_child)
	{
		if (ft_strcmp(cmd, "cd") == 0)
			return (ft_cd(shell, i), 1);
		if (ft_strcmp(cmd, "exit") == 0)
			return (ft_exit(shell, shell->cmds[i].args), 1);
		if (ft_strcmp(cmd, "export") == 0 && shell->cmds[i].args[1])
			return (ft_export(shell, shell->cmds[i].args), 1);
		if (ft_strcmp(cmd, "unset") == 0)
			return (ft_unset(shell, shell->cmds[i].args[1]), 1);
	}
	if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(shell, shell->cmds[i].args);
	else if (ft_strcmp(cmd, "export") == 0 && !shell->cmds[i].args[1])
		print_export(shell);
	else
		return (0);
	return (1);
}
