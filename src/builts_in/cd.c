/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:56:58 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/26 14:09:46 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	ft_cd(t_shell *shell, int index)
{
	if (chdir(shell->cmds[index].args[1]) != 0)
		ft_putstr_fd("Error with cd\n", 2);
	else
		printf("c'est bon je t'ai bouger bobby!\n");
}
