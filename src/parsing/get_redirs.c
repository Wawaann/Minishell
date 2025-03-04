/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:02:53 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/04 19:36:46 by ebigotte         ###   ########.fr       */
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

int	get_number_redir(t_token *tokens, bool in)
{
	int	i;
	int	redir;

	i = 0;
	redir = 0;
	while (tokens[i].token && ft_strcmp(tokens[i].token, "|") != 0)
	{
		if (in)
		{
			if (is_redirs(tokens[i].token) == 1
				|| is_redirs(tokens[i].token) == 2)
				redir++;
		}
		else
		{
			if (is_redirs(tokens[i].token) == 3
				|| is_redirs(tokens[i].token) == 4)
				redir++;
		}
		i++;
	}
	return (redir);
}

void	get_redir(t_command *cmd, t_token *token, int i)
{
	static int	redir = 0;

	if (!cmd->redirs[0].file)
		redir = 0;
	cmd->redirs[redir].type = is_redirs(token[i].token);
	cmd->redirs[redir].file = ft_strtrim(token[i + 1].token, "\"'");
	redir++;
}

void	get_redirs(t_command *cmds, t_token *tokens, int *i)
{
	get_redir(cmds, tokens, *i);
	(*i)++;
}
