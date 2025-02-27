/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:56:58 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/27 11:24:20 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	ft_cd(t_shell *shell, int index)
{
	char	*cwd;
	char	*var;
	char	*name;

	cwd = NULL;
	var = NULL;
	name = NULL;
	if (chdir(shell->cmds[index].args[1]) != 0)
		ft_putstr_fd("Error with cd\n", 2);
	else
	{
		cwd = getcwd(NULL, 0);
		name = ft_strdup("PWD=");
		var = ft_strjoin(name, cwd);
		ft_export(shell, var);
		free(var);
		free(name);
		free(cwd);
		printf("c'est bon je t'ai bouger bobby!\n");
	}
}
