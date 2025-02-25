/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:13:03 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/25 18:17:58 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

/*
	- Create double tab for pipes
		there are num_cmds-1 pipes => malloc(sizeof(int *) * (shell->num_cmds - 1))
	- Create all necessary pipes
		every pipe need two fd => malloc(sizeof(int) * 2);
*/

void	init_pipes(t_shell *shell)
{
	int	i;

	shell->pipes = malloc(sizeof(int *) * (shell->num_cmds - 1));
	if (!shell->pipes)
	{
		free_shell(shell);
		ft_error("Error allocating memory for pipes\n");
	}
	i = 0;
	while (i < shell->num_cmds - 1)
	{
		shell->pipes[i] = malloc(sizeof(int) * 2);
		if (!shell->pipes[i])
		{
			free_shell(shell);
			ft_error("Error allocating memory for pipe\n");
		}
		if (pipe(shell->pipes[i]) == -1)
		{
			free_shell(shell);
			ft_error("Pipe error\n");
		}
		i++;
	}
}

/*
	first command (index == 0)
		-> redirect stdout into next pipe
	last command
		-> redirect stdin into prev pipe
	middle command
		-> redirect stdin into prev pipe
		-> redirect stdout into next pipe

	Close all the unuse pipes
	Dup2 copies the pipes and redirects these copies.
	You therefore need to close all the original pipes (those before the copy)
	to avoid blocking.
*/

void	redirect_pipes(t_shell *shell, int index)
{
	int i;

	if (index == 0)
		dup2(shell->pipes[index][1], STDOUT_FILENO);
	else if (index == shell->num_cmds - 1)
		dup2(shell->pipes[index - 1][0], STDIN_FILENO);
	else
	{
		dup2(shell->pipes[index - 1][0], STDIN_FILENO);
		dup2(shell->pipes[index][1], STDOUT_FILENO);
	}
	i = 0;
	while (i < shell->num_cmds - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
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
			if (shell->cmds[index].out->type == 3) // >
				fd = open(shell->cmds[index].out[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // TRUNC pour ecraser l'ancien resultat (644 = Lecture + écriture pour le propriétaire les autres peuvent seulement lire)
			else if (shell->cmds[index].out->type == 4) // >>
				fd = open(shell->cmds[index].out[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644); // APPEND pour ajouter a la suite de l'ancien resultat
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

void collect_all_heredocs(t_shell *shell)
{
	int		i;
	int		j;
	char	*nb_heredoc;
	char	*name;

	i = 0;
	while (i < shell->num_cmds)
	{
		if (shell->cmds[i].in_count > 0)
		{
			j = 0;
			while (j < shell->cmds[i].in_count)
			{
				if (shell->cmds[i].in[j].type == 2)
				{
					nb_heredoc = ft_itoa(j);
					name = ft_strjoin(".heredoc_tmp_", nb_heredoc);
					free(nb_heredoc);
					read_hd(shell, shell->cmds[i].in[j].file, name);
					free(name);
				}
				j++;
			}
		}
		i++;
	}
}

void redirect_heredoc(t_shell *shell, int index)
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


/*
	- Call redirect pipes function
	- Checkif I have the path for the command
	- Execute the command
*/

void	call_execve(t_shell *shell, int index)
{
	redirect_heredoc(shell, index);
	redirect_pipes(shell, index);
	redirect_infiles(shell, index);
	redirect_outfiles(shell, index);

	if (shell->path[index] == NULL)
	{
		free_shell(shell);
		ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	execve(shell->path[index], shell->cmds[index].args, shell->env);
}

/*
	Parent process need to wait that all child are finished
*/

void	ft_wait_childs(t_shell *shell)
{
	int		i;

	i = 0;
	while (i < shell->num_cmds)
	{
		wait(&shell->exit_status);
		i++;
	}
}

/*
	all pipes needs to be close because they are useless in parrent process
*/

void	ft_close_pipes(t_shell *shell)
{
	int		i;

	i = 0;
	while (i < shell->num_cmds - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

/*
	- Create a child process for every command
	- Then execute each cmd on each child
*/

void	execute_pipe(t_shell *shell)
{
	int		i;
	pid_t	pid;

	collect_all_heredocs(shell);
	i = 0;
	while (i < shell->num_cmds)
	{
		pid = fork();
		if (pid == -1)
			ft_error("Error with fork");
		if (pid == 0)
		{
			call_execve(shell, i);
			exit(127);
		}
		i++;
	}
	ft_close_pipes(shell);
	ft_wait_childs(shell);
	cleanup_heredocs(shell);
}

void	execute_simple_cmd(t_shell *shell)
{
	pid_t	pid;

	collect_all_heredocs(shell);
	pid = fork();
	if (pid == -1)
		ft_error("Error with fork");
	if (pid == 0)
	{
		redirect_heredoc(shell, 0);
		redirect_infiles(shell, 0);
		redirect_outfiles(shell, 0);
		execve(shell->path[0], shell->cmds[0].args, shell->env);
		exit(127);
	}
	else
		wait(&shell->exit_status);
	cleanup_heredocs(shell);
}

void	execute_command(t_shell *shell)
{
	if (shell->num_cmds > 1)
		execute_pipe(shell);
	else
		execute_simple_cmd(shell);
}
