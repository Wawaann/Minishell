/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:56:58 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/03 18:26:21 by cedmarti         ###   ########.fr       */
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

int	check_args(t_shell *shell, char **path, int index)
{
	if (shell->cmds[index].args[1] && shell->cmds[index].args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	if (!(*path))
	{
		*path = getenv("HOME");
		if (!(*path))
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (0);
		}
	}
	return (0);
}

int	check_access(t_shell *shell, char *path)
{
	if (ft_strcmp(path, "$PWD") == 0)
		return (0);
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	if (access(path, X_OK) != 0)
	{
		ft_putstr_fd("cd: permission denied\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

void	ft_cd(t_shell *shell, int index)
{
	char	*cwd;
	char	*var;
	char	*name;
	char	*path;

	cwd = NULL;
	var = NULL;
	name = NULL;
	path = shell->cmds[index].args[1];
	if (check_args(shell, &path, index) == 1 || check_access(shell, path) == 1)
		return ;
	if (chdir(path) != 0)
		return ;
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
