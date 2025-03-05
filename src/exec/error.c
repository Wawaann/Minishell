/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:51:50 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/05 14:52:19 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	else
		return (0);
}

int	get_exit_code(void)
{
	int err;

	err = errno;
	if (err == ENOENT) // Fichier introuvable ou commande not found
		return (127);
	if (err == EISDIR) // C'est un dossier
		return (126);
	if (err == EACCES) // Permission refuse
		return (126);
	return (1);
}

void	handle_exec_error(t_shell *shell, int index)
{
	int		err;
	char	*arg;

	err = errno;
	arg = shell->cmds[index].args[0];
	if (index == shell->num_cmds - 1)
	{
		if ((err == ENOENT || err == EACCES) && !ft_strchr(arg, '/'))
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
		else
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(err), 2);
			ft_putstr_fd("\n", 2);
			shell->exit_status = get_exit_code();
		}
	}
	exit(shell->exit_status);
}
