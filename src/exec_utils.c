/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:13:03 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/27 11:47:12 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

/*
	- Browse environment variables until you find 'PATH'
	- Return double tab with all path possibles separate by ':'
		/home/cedmarti/bin
		/usr/local/sbin
		/usr/local/bin
		/usr/sbin
		/usr/bin/
		/sbin
		/bin
		/usr/games
		/usr/local/games
		/snap/bin
*/

char	**get_all_path(t_shell *shell)
{
	char	**path;
	int		i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PATH", 4) == 0)
		{
			path = ft_split(shell->env[i] + 5, ":");
			return (path);
		}
		i++;
	}
	return (NULL);
}

/*
	- Try all path to find the right one
		- add "/" + "command name" to the path
		- check with access() if the command exist and if we have the right to execute it
	- Return the right pass if there is one
*/

char	*get_path(t_shell *shell, char *cmd_name)
{
	char	**all_path;
	char	*mid_path;
	char	*path;
	int		i;

	if (cmd_name && access(cmd_name, F_OK | X_OK) == 0)
		return (ft_strdup(cmd_name));
	all_path = get_all_path(shell);
	i = 0;
	while (all_path[i])
	{
		mid_path = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(mid_path, cmd_name);
		free(mid_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_tokens(all_path);
			return (path);
		}
		free(path);
		i++;
	}
	free_tokens(all_path);
	return (NULL);
}

/*
	multiple commands = multiple paths
	- allocate memory for a double tab of paths
	- save each good path into the double tab
	(path[0] = path for command[0] ...)
*/

void	init_path(t_shell *shell)
{
	int	i;

	i = 0;
	shell->path = ft_calloc(shell->num_cmds + 1, sizeof(char *));
	if (!shell->path)
	{
		free_shell(shell);
		ft_error("Error allocating memory for paths\n");
	}
	while (i < shell->num_cmds)
	{
		shell->path[i] = get_path(shell, shell->cmds[i].args[0]);
		i++;
	}
}
