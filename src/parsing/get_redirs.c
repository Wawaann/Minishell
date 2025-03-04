/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:02:53 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/04 14:18:43 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int	is_redirs(char *token)
{
	if (ft_strncmp(token, "<", 2) == 0)
		return (1);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (2);
	if (ft_strncmp(token, ">", 2) == 0)
		return (3);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (4);
	return (0);
}

void	get_number_redir(t_token *tokens, int *count, bool in)
{
	int	i;
	int	redir;

	i = 0;
	redir = 0;
	while (tokens[i].token && ft_strcmp(tokens[i].token, "|") != 0)
	{
		if (in)
		{
			if (is_redirs(tokens[i].token) == 1 || is_redirs(tokens[i].token) == 2)
				redir++;
		}
		else
		{
			if (is_redirs(tokens[i].token) == 3 || is_redirs(tokens[i].token) == 4)
				redir++;
		}
		i++;
	}
	(*count) = redir;
}

void	get_in_redir(t_command *cmd, t_token *tokens, int i)
{
	static int	in = 0;

	if (!cmd->in[0].file)
		in = 0;
	cmd->in[in].type = is_redirs(tokens[i].token);
	cmd->in[in].file = ft_strtrim(tokens[i + 1].token, "\"'");
	in++;
}

void	get_out_redir(t_command *cmd, t_token *tokens, int i)
{
	static int	out = 0;

	if (!cmd->out[0].file)
		out = 0;
	cmd->out[out].type = is_redirs(tokens[i].token);
	cmd->out[out].file = ft_strtrim(tokens[i + 1].token, "\"'");
	out++;
}

void	get_redirs(t_command *cmds, t_token *tokens, int *i)
{
	if (ft_strcmp(tokens[*i].token, "<") == 0 || ft_strcmp(tokens[*i].token, "<<") == 0)
		get_in_redir(cmds, tokens, *i);
	if (ft_strcmp(tokens[*i].token, ">") == 0 || ft_strcmp(tokens[*i].token, ">>") == 0)
		get_out_redir(cmds, tokens, *i);
	(*i)++;
}
