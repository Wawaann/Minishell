/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:45:09 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/26 12:04:04 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	read_hd(t_shell *shell, char *limiter, char *name)
{
	char	*line;
	int		fd;

	(void)shell;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 00777);
	if (fd == -1)
		ft_error("No such file or directory hd\n");
	while (1)
	{
		line = readline("heredoc > ");
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
}

void	collect_all_heredocs(t_shell *shell)
{
	int		i;
	int		j;
	char	*nb_heredoc;
	char	*name;

	i = -1;
	while (++i < shell->num_cmds)
	{
		if (shell->cmds[i].in_count > 0)
		{
			j = -1;
			while (++j < shell->cmds[i].in_count)
			{
				if (shell->cmds[i].in[j].type == 2)
				{
					nb_heredoc = ft_itoa(j);
					name = ft_strjoin(".heredoc_tmp_", nb_heredoc);
					free(nb_heredoc);
					read_hd(shell, shell->cmds[i].in[j].file, name);
					free(name);
				}
			}
		}
	}
}

void	redirect_heredoc(t_shell *shell, int index)
{
	int		fd;
	int		i;
	char	*nb_heredoc;
	char	*name;

	if (shell->cmds[index].in_count > 0)
	{
		i = shell->cmds[index].in_count - 1;
		if (shell->cmds[index].in[i].type == 2)
		{
			nb_heredoc = ft_itoa(i);
			name = ft_strjoin(".heredoc_tmp_", nb_heredoc);
			free(nb_heredoc);
			fd = open(name, O_RDONLY);
			if (fd == -1)
				ft_error("No such file or directory\n");
			dup2(fd, STDIN_FILENO);
			close(fd);
			free(name);
		}
	}
}

void	cleanup_heredocs(t_shell *shell)
{
	int		i;
	char	*nb_heredoc;
	char	*name;

	i = 0;
	while (i < shell->cmds[0].in_count)
	{
		nb_heredoc = ft_itoa(i);
		name = ft_strjoin(".heredoc_tmp_", nb_heredoc);
		free(nb_heredoc);
		unlink(name);
		free(name);
		i++;
	}
}
