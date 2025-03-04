/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:13:03 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/04 14:26:52 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

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

char	*get_path(t_shell *shell, char *cmd_name)
{
	char	**all_path;
	char	*mid_path;
	char	*path;
	int		i;

	if (cmd_name && access(cmd_name, F_OK | X_OK) == 0)
		return (ft_strdup(cmd_name));
	all_path = get_all_path(shell);
	if (all_path == NULL)
		return (NULL);
	i = 0;
	while (all_path[i])
	{
		mid_path = ft_strjoin(all_path[i++], "/");
		path = ft_strjoin(mid_path, cmd_name);
		free(mid_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_tokens(all_path);
			return (path);
		}
		free(path);
	}
	free_tokens(all_path);
	return (NULL);
}

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

void	redirect_simple_cmd(t_shell *shell)
{
	redirect_heredoc(shell, 0);
	redirect_infiles(shell, 0);
	redirect_outfiles(shell, 0);
}

void	ft_wait(t_shell *shell)
{
	int	status;

	wait(&status);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}
