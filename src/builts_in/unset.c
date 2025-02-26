/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:46:00 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/26 17:56:55 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	ft_unset(t_shell *shell, char *var)
{
	int	i;
	int	j;

	if (!var)
		return ;
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, ft_strlen(var)) == 0
			&& shell->env[i][strlen(var)] == '=')
		{
			free(shell->env[i]);
			j = i;
			while (shell->env[j])
			{
				shell->env[j] = shell->env[j+1];
				j++;
			}
			break ;
		}
		i++;
	}
}
