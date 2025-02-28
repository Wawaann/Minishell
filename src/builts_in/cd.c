/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:56:58 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/28 16:40:26 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	update_pwd(t_shell *shell, char *var)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(var);
			return ;
		}
		i++;
	}
}

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
		update_pwd(shell, var);
		free(var);
		free(name);
		free(cwd);
	}
}
