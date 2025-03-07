/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:43:41 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/07 11:31:05 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	handle_redir_error(t_shell *shell, int index, int i)
{
	char	*file;

	file = shell->cmds[index].redirs[i].file;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	shell->exit_status = 1;
	free_shell(shell, false, true);
	exit(shell->exit_status);
}

int	redir_in(t_command *cmds, int i, int *fd_in, int *j)
{
	*fd_in = open(cmds->redirs[i].file, O_RDONLY);
	if (*fd_in == -1)
		return (1);
	if (*j == cmds->in - 1 && *fd_in != -1)
		dup2(*fd_in, STDIN_FILENO);
	if (*fd_in != -1)
	{
		close(*fd_in);
		(*j)++;
	}
	return (0);
}

int	redir_out(t_command *cmds, int i, int *fd_out, int j)
{
	int	type;

	type = cmds->redirs[i].type;
	if (type == 3)
		*fd_out = open(cmds->redirs[i].file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == 4)
		*fd_out = open(cmds->redirs[i].file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd_out == -1)
		return (1);
	if (*fd_out != -1 && i - j == cmds->out - 1 && type != 1)
	{
		dup2(*fd_out, STDOUT_FILENO);
		close(*fd_out);
	}
	return (0);
}

void	redirect(t_shell *shell, int index)
{
	int	fd_in;
	int	fd_out;
	int	i;
	int	j;

	fd_in = -2;
	fd_out = -2;
	i = 0;
	j = 0;
	if (shell->cmds[index].count > 0)
	{
		while (i < shell->cmds[index].count)
		{
			if (shell->cmds[index].redirs[i].type == 1)
				if (redir_in(&shell->cmds[index], i, &fd_in, &j) == 1)
					handle_redir_error(shell, index, i);
			if (shell->cmds[index].redirs[i].type == 3
				|| shell->cmds[index].redirs[i].type == 4)
				if (redir_out(&shell->cmds[index], i, &fd_out, j) == 1)
					handle_redir_error(shell, index, i);
			i++;
		}
	}
}
