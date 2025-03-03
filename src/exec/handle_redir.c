/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:43:41 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/03 18:29:50 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	handle_redir_error(t_shell *shell, int index, int i, int infile)
{
	char	*file;

	if (infile)
		file = shell->cmds[index].in[i].file;
	else
		file = shell->cmds[index].out[i].file;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	shell->exit_status = 1;
	exit(shell->exit_status);
}

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
				handle_redir_error(shell, index, i, 0);
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
					handle_redir_error(shell, index, i, 1);
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
