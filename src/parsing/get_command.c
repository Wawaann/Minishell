/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:20:09 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/28 17:20:39 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int	get_number_args(char **tokens)
{
	int	i;
	int	args;

	i = 0;
	args = 0;
	while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
	{
		if (is_redirs(tokens[i]))
			args -= 2;
		args++;
		i++;
	}
	return (args);
}

void	init_cmd(t_command *cmd, char **tokens)
{
	get_number_redir(tokens, &cmd->in_count, true);
	get_number_redir(tokens, &cmd->out_count, false);
	cmd->args = ft_calloc(get_number_args(tokens) + 1, sizeof(char *));
	cmd->in = ft_calloc(cmd->in_count + 1, sizeof(t_redirs));
	cmd->out = ft_calloc(cmd->out_count + 1, sizeof(t_redirs));
}

bool	is_var(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

char	*get_args(char *token, char *cmd)
{
	char	*args;

	if (cmd && ft_strncmp(cmd, "echo", 4) == 0)
	{
		if (is_var(token))
			args = ft_strtrim(token, "'");
		else
			args = ft_strtrim(token, "\"'");
	}
	else if (cmd && ft_strncmp(cmd, "export", 6) == 0)
		args = ft_strtrim(token, "'");
	else
		args = ft_strtrim(token, "\"'");
	return (args);
}

t_command	*get_commands(char **tokens, int cmd_nums)
{
	t_command	*cmds;
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	k = 0;
	cmds = ft_calloc(cmd_nums + 1, sizeof(t_command));
	init_cmd(&cmds[j], tokens);
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			j++;
			k = 0;
			init_cmd(&cmds[j], tokens + i + 1);
		}
		else if (is_redirs(tokens[i]))
			get_redirs(&cmds[j], tokens, &i);
		else
			cmds[j].args[k++] = get_args(tokens[i], cmds[j].args[0]);
		i++;
	}
	return (cmds);
}
