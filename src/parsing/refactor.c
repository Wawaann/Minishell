/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:17:41 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/07 16:46:31 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*get_terminal_pid(void)
{
	int		fd;
	pid_t	term_pgid;
	char	*pid_str;

	fd = open("/dev/tty", O_RDONLY);
	if (fd == -1)
		return (perror("open"), ft_strdup("0"));
	if (ioctl(fd, TIOCGPGRP, &term_pgid) == -1)
		return (perror("ioctl"), close(fd), ft_strdup("0"));
	close(fd);
	pid_str = ft_itoa(term_pgid);
	return (pid_str);
}

char	*s_case(char *str, int *i, int exit_status)
{
	if (str[*i + 1] == '?')
	{
		(*i) += 2;
		return (ft_itoa(exit_status));
	}
	else if (str[*i + 1] == '$')
	{
		(*i) += 2;
		return (get_terminal_pid());
	}
	else if (str[*i + 1] == ' ' || str[*i + 1] == '\0')
	{
		(*i)++;
		return (ft_strndup("$", 1));
	}
	return (NULL);
}

static char	*get_var(t_shell *shell, char *token, int *i, int *f)
{
	char	*var_name;
	char	*var_value;
	int		start;

	start = ++(*i);
	while (token[*i] && token[*i] != ' ' && token[*i] != '$')
		(*i)++;
	var_name = ft_strndup(&token[start], *i - start);
	var_value = get_env_var(shell->env, var_name);
	free(var_name);
	if (!var_value)
	{
		*f = 1;
		return (ft_strdup(""));
	}
	*f = 0;
	return (var_value);
}

static char	*append_token_part(char *result, char *token, int *i)
{
	int		start;
	char	*tmp;

	start = *i;
	while (token[*i] && token[*i] != '$')
		(*i)++;
	tmp = ft_strndup(&token[start], *i - start);
	result = gnl_strjoin(result, tmp);
	free(tmp);
	return (result);
}

char	*refactor_token(t_shell *shell, int count)
{
	int		i;
	int		f;
	char	*result;
	char	*var;

	result = ft_strdup("");
	i = 0;
	while (shell->tokens[count].token[i])
	{
		if (shell->tokens[count].token[i] == '$')
		{
			var = s_case(shell->tokens[count].token, &i, shell->exit_status);
			if (!var)
				var = get_var(shell, shell->tokens[count].token, &i, &f);
			result = gnl_strjoin(result, var);
			if (f)
				free(var);
		}
		else
			result = append_token_part(result, shell->tokens[count].token, &i);
	}
	free(shell->tokens[count].token);
	return (result);
}
