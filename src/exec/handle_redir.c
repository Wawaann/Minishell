/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:43:41 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/04 20:09:57 by ebigotte         ###   ########.fr       */
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
	exit(shell->exit_status);
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
			{
				// Input redirection
				fd_in = open(shell->cmds[index].redirs[i].file, O_RDONLY);
				if (fd_in == -1)
					handle_redir_error(shell, index, i);
				// Duplicate input only at the last redirection
				if (j == shell->cmds[index].in - 1 && fd_in != -1)
				{
					dup2(fd_in, STDIN_FILENO);
				}
				// Only close if successfully opened
				if (fd_in != -1)
				{
					close(fd_in);
					j++;
				}
			}
			else if (shell->cmds[index].redirs[i].type == 3)
			{
				// Truncate output
				fd_out = open(shell->cmds[index].redirs[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
			else if (shell->cmds[index].redirs[i].type == 4)
			{
				// Append output
				fd_out = open(shell->cmds[index].redirs[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			}
			if (fd_out == -1)
				handle_redir_error(shell, index, i);
			// Handle output redirection
			if (fd_out != -1 && i - j == shell->cmds[index].out - 1 && shell->cmds[index].redirs[i].type != 1)
			{
				dup2(fd_out, STDOUT_FILENO);
				close(fd_out);
			}
			i++;
		}
	}
}
