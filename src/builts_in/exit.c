/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:17:24 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/28 18:16:23 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	ft_exit(t_shell *shell, char **args)
{
	int	exit_status;

	exit_status = 0;
	if (ft_tablen(args) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		shell->exit_status = 1;
		return ;
	}
	if (args[1] && ft_strdigit(args[1]) == 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if (args[1])
		exit_status = ft_atoi(args[1]);
	if (exit_status < 0)
		exit_status = 256 + exit_status;
	else
		exit_status = exit_status % 256;
	free_tokens(shell->env);
	free_shell(shell);
	exit(exit_status);
}
