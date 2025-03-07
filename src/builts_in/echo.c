/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:31:21 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/07 15:40:55 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	ft_echo(t_shell *shell, int count)
{
	bool	newline;
	int		i;

	i = 1;
	newline = true;
	if (shell->cmds[count].args[i]
		&& strcmp(shell->cmds[count].args[i], "-n") == 0)
	{
		newline = false;
		i++;
	}
	while (shell->cmds[count].args[i])
	{
		printf("%s", shell->cmds[count].args[i]);
		if (shell->cmds[count].args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
