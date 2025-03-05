/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:31:21 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/05 17:59:45 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	get_terminal_pgid(void)
{
	int		fd;
	pid_t	term_pgid;

	fd = open("/dev/tty", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (ioctl(fd, TIOCGPGRP, &term_pgid) == -1)
	{
		perror("ioctl");
		close(fd);
		return ;
	}
	close(fd);
	printf("%d", term_pgid);
}

void	display_loop(t_shell *shell, char *var, char *value, int *i)
{
	char	*tmp;

	if (var[(*i)] == ' ')
		printf("$");
	else if (var[(*i)] == '?')
	{
		printf("%d", shell->exit_status);
		(*i)++;
	}
	else if (var[(*i)] == '$')
	{
		if (var[++(*i)] == '$')
			get_terminal_pgid();
	}
	else
	{
		tmp = ft_substr(var, (*i), ft_strlen_to(var + (*i), '$'));
		value = getenv(tmp);
		if (value)
			printf("%s", value);
		else
			printf("%s", tmp);
		(*i) += ft_strlen(tmp);
		free(tmp);
	}
}

void	print_env_var(t_shell *shell, char *var)
{
	char	*value;
	int		i;

	if (!var || var[0] == '\0' || var[0] == ' ')
	{
		printf("$");
		return ;
	}
	i = 0;
	value = NULL;
	while (var[i])
		display_loop(shell, var, value, &i);
}

void	print_argument(t_shell *shell, const char *arg, int echo)
{
	int		i;
	int		start;
	char	*var;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && echo)
		{
			start = ++i;
			while (arg[i] && (arg[i] != ' ' && arg[i] != '"'
					&& arg[i] != '\''))
				i++;
			var = ft_strndup(&arg[start], i - start);
			print_env_var(shell, var);
			free(var);
			i--;
		}
		else
			printf("%c", arg[i]);
		i++;
	}
}

void	ft_echo(t_shell *shell, char **args, int *echo)
{
	bool	newline;
	int		i;

	i = 1;
	newline = true;
	if (args[i] && strcmp(args[i], "-n") == 0)
	{
		newline = false;
		i++;
	}
	while (args[i])
	{
		print_argument(shell, args[i], echo[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
