/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:51:50 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/10 13:53:38 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	else
		return (0);
}

int	get_exit_code(void)
{
	int	err;

	err = errno;
	if (err == ENOENT)
		return (127);
	if (err == EISDIR)
		return (126);
	if (err == EACCES)
		return (126);
	return (1);
}

void	display_error(t_shell *shell, char *arg, int index, int err)
{
	if ((err == ENOENT || err == EACCES) && !ft_strchr(arg, '/')
		&& shell->cmds[index].num_args > 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_status = 127;
	}
	else if (is_directory(arg) && access(arg, F_OK) == 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		shell->exit_status = 126;
	}
	else if (shell->cmds[index].num_args > 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(err), 2);
		ft_putstr_fd("\n", 2);
		shell->exit_status = get_exit_code();
	}
}

void	handle_exec_error(t_shell *shell, int index)
{
	int		err;
	char	*arg;

	err = errno;
	arg = shell->cmds[index].args[0];
	if (index == shell->num_cmds - 1)
		display_error(shell, arg, index, err);
	free_shell(shell, true, true);
	exit(shell->exit_status);
}
