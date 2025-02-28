/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builts_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:11 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/28 18:15:07 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

int	handle_builtins(t_shell *shell, int i)
{
	char	*cmd;

	if (!shell->cmds[i].args[0])
		return (0);
	cmd = shell->cmds[i].args[0];
	if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(shell, shell->cmds[i].args);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(shell, shell->cmds[i].args[1]);
	else if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(shell, shell->cmds[i].args);
	else
		return (0);
	return (1);
}
