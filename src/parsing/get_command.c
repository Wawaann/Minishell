/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:20:09 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/05 17:08:31 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int	get_number_args(t_token *tokens)
{
	int	i;
	int	args;

	i = 0;
	args = 0;
	while (tokens[i].token && ft_strcmp(tokens[i].token, "|") != 0)
	{
		if (is_redirs(tokens[i].token))
			args -= 2;
		if (tokens[i].valid)
			args++;
		i++;
	}
	return (args);
}

void	init_cmd(t_command *cmd, t_token *tokens)
{
	cmd->num_args = get_number_args(tokens);
	cmd->args = ft_calloc(cmd->num_args + 1, sizeof(char *));
	cmd->echo = ft_calloc(get_number_args(tokens) + 1, sizeof(int));
	cmd->in = get_number_redir(tokens, true);
	cmd->out = get_number_redir(tokens, false);
	cmd->count = cmd->in + cmd->out;
	cmd->redirs = ft_calloc(cmd->count + 1, sizeof(t_redirs));
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

char	*get_args(t_token token, t_command *cmd, int *k)
{
	char	*args;

	if (cmd->args[0] && ft_strncmp(cmd->args[0], "echo", 4) == 0)
	{
		if (is_var(token.token) && token.echo)
			cmd->echo[*k] = 1;
		else
			cmd->echo[*k] = 0;
		args = ft_strdup(token.token);
	}
	else if (cmd->args[0] && ft_strncmp(cmd->args[0], "export", 6) == 0)
		args = ft_strdup(token.token);
	else
		args = ft_strtrim(token.token, "\"'");
	(*k)++;
	return (args);
}

t_command	*get_commands(t_token *tokens, int cmd_nums)
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
	while (tokens[i].token)
	{
		if (ft_strcmp(tokens[i].token, "|") == 0 && tokens[i].valid)
		{
			j++;
			k = 0;
			init_cmd(&cmds[j], tokens + i + 1);
		}
		else if (is_redirs(tokens[i].token) && tokens[i].valid)
			get_redirs(&cmds[j], tokens, &i);
		else if (tokens[i].valid)
			cmds[j].args[k] = get_args(tokens[i], &cmds[j], &k);
		i++;
	}
	return (cmds);
}
