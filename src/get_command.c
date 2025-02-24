/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:20:09 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/23 11:36:31 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

bool	is_redirection(char *token)
{
	if (ft_strncmp(token, ">", 1) == 0 || ft_strncmp(token, "<", 1) == 0)
		return (true);
	if (ft_strncmp(token, ">>", 2) == 0 || ft_strncmp(token, "<<", 2) == 0)
		return (true);
	return (false);
}

int	get_number_args(char **tokens)
{
	int	i;
	int	args;

	i = 0;
	args = 0;
	while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
	{
		if (is_redirection(tokens[i]))
			args -= 2;
		args++;
		i++;
	}
	return (args);
}

t_command	*get_commands(char **tokens, int cmd_nums)
{
	t_command   *cmds;
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	k = 0;
	cmds = ft_calloc(cmd_nums + 1, sizeof(t_command));
	cmds[j].args = ft_calloc(get_number_args(tokens) + 1, sizeof(char *));
	cmds[j].in = NULL;
	cmds[j].out = NULL;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			cmds[j].args[k] = NULL;
			j++;
			k = 0;
			cmds[j].args = ft_calloc(get_number_args(tokens + i + 1) + 1, sizeof(char *));
			cmds[j].in = NULL;
			cmds[j].out = NULL;
		}
		else if (is_redirection(tokens[i]))
		{
			if (ft_strncmp(tokens[i], ">", 1) == 0)
			{
				cmds[j].out = ft_calloc(1, sizeof(t_redirection));
				cmds[j].out->file = ft_strdup(tokens[i + 1]);
				cmds[j].out->type = 1;
			}
			else if (ft_strncmp(tokens[i], ">>", 2) == 0)
			{
				cmds[j].out = ft_calloc(1, sizeof(t_redirection));
				cmds[j].out->file = ft_strdup(tokens[i + 1]);
				cmds[j].out->type = 2;
			}
			else if (ft_strncmp(tokens[i], "<", 1) == 0)
			{
				cmds[j].in = ft_calloc(1, sizeof(t_redirection));
				cmds[j].in->file = ft_strdup(tokens[i + 1]);
				cmds[j].in->type = 1;
			}
			else if (ft_strncmp(tokens[i], "<<", 2) == 0)
			{
				cmds[j].in = ft_calloc(1, sizeof(t_redirection));
				cmds[j].in->file = ft_strdup(tokens[i + 1]);
				cmds[j].in->type = 2;
			}
			i++;
		}
		else
		{
			cmds[j].args[k] = ft_strdup(tokens[i]);
			k++;
		}
	}
	return (cmds);
}
