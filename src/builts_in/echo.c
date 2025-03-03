/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:31:21 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/03 14:56:11 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

int	print_spe(char *arg, int *i, t_shell *shell)
{
	if (arg[*i + 1] == '?')
	{
		printf("%d", shell->exit_status);
		(*i)++;
		return (1);
	}
	else if (arg[*i + 1] == '$')
	{
		printf("%d", g_sig_pid);
		(*i)++;
		return (1);
	}
	else if (arg[*i + 1] == ' ')
	{
		printf("$");
		(*i)++;
		return (1);
	}
	return (0);
}

void	print_var(char *arg, int *i, t_shell *shell)
{
	char	*var;

	if (print_spe(arg, i, shell) == 1)
		return ;
	var = get_env_var(shell->env, arg + *i + 1);
	if (var)
	{
		printf("%s", var);
		(*i) += ft_strlen(var) + 1;
		free(var);
	}
	else
		(*i) += ft_strlen_to(arg + *i + 1, ' ');
}

void	display_var(t_shell *shell, char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			print_var(arg, &i, shell);
		}
		else
		{
			printf("%c", arg[i]);
		}
		i++;
	}
}

void	display_echo(t_shell *shell, char **args, int start)
{
	int		i;
	char	*tmp;

	i = start;
	while (args[i])
	{
		if (is_var(args[i]) && args[i][0] != '\'')
		{
			display_var(shell, args[i]);
		}
		else
		{
			tmp = ft_strtrim(args[i], "'");
			printf("%s", tmp);
			free(tmp);
		}
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

void	ft_echo(t_shell *shell, char **args)
{
	if (args[1] && strcmp(args[1], "-n") == 0)
	{
		display_echo(shell, args, 2);
	}
	else
	{
		display_echo(shell, args, 1);
		printf("\n");
	}
}
