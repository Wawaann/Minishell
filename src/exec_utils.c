/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:13:03 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/19 18:06:56 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	free_double_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**get_all_path(t_shell *shell)
{
	char	**path;
	int		i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PATH", 4) == 0)
		{
			path = ft_split(shell->env[i] + 5, ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(t_shell *shell, char *cmd_name)
{
	char	**all_path;
	char	*mid_path;
	char	*path;
	int		i;

	all_path = get_all_path(shell);
	i = 0;
	while (all_path[i])
	{
		mid_path = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(mid_path, cmd_name);
		free(mid_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_double_tab(all_path);
			return (path);
		}
		free(path);
		i++;
	}
	free_double_tab(all_path);
	return (NULL);
}

void	init_path(t_shell *shell)
{
	int	i;

	i = 0;
	shell->path = malloc(sizeof(char *) * (shell->num_cmds + 1));
	if (!shell->path)
	{
		// free ce qui a ete allouer
		ft_error("Error allocating memory for paths\n");
	}
	while (i < shell->num_cmds)
	{
		shell->path[i] = get_path(shell, shell->cmds[i][0]);
		i++;
	}
	shell->path[i] = NULL;
}
