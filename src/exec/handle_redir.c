/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:43:41 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/26 11:59:25 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	redirect_outfiles(t_shell *shell, int index)
{
	int	fd;
	int	i;

	fd = 0;
	i = 0;
	if (shell->cmds[index].out_count > 0)
	{
		while (i < shell->cmds[index].out_count)
		{
			if (shell->cmds[index].out->type == 3)
				fd = open(shell->cmds[index].out[i].file, O_WRONLY | O_CREAT
						| O_TRUNC, 0644);
			else if (shell->cmds[index].out->type == 4)
				fd = open(shell->cmds[index].out[i].file, O_WRONLY | O_CREAT
						| O_APPEND, 0644);
			if (fd == -1)
				ft_error("No such file or directory\n");
			if (i == shell->cmds[index].out_count - 1)
				dup2(fd, STDOUT_FILENO);
			close(fd);
			i++;
		}
	}
}

void	redirect_infiles(t_shell *shell, int index)
{
	int	fd;
	int	i;

	fd = -1;
	i = 0;
	if (shell->cmds[index].in_count > 0)
	{
		while (i < shell->cmds[index].in_count)
		{
			if (shell->cmds[index].in[i].type == 1)
			{
				fd = open(shell->cmds[index].in[i].file, O_RDONLY);
				if (fd == -1)
					ft_error("No such file or directory\n");
			}
			i++;
		}
		i = shell->cmds[index].in_count - 1;
		if (fd != -1 && shell->cmds[index].in[i].type == 1)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
}
