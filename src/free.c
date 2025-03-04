/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:00:37 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/04 15:46:28 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token)
		free(tokens[i++].token);
	free(tokens);
}

void	free_path_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->path)
	{
		while (i < shell->num_cmds)
		{
			if (shell->path[i])
				free(shell->path[i]);
			i++;
		}
		free(shell->path);
	}
	if (shell->pipes)
	{
		i = 0;
		while (i < shell->num_cmds - 1)
		{
			free(shell->pipes[i]);
			i++;
		}
		free(shell->pipes);
	}
}

void	free_cmds(t_command *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i].args)
	{
		j = 0;
		while (cmds[i].args[j])
			free(cmds[i].args[j++]);
		free(cmds[i].args);
		j = 0;
		while (cmds[i].in[j].file)
			free(cmds[i].in[j++].file);
		free(cmds[i].in);
		j = 0;
		while (cmds[i].out[j].file)
			free(cmds[i].out[j++].file);
		free(cmds[i].out);
		free(cmds[i].echo);
		i++;
	}
	free(cmds);
}

void	free_shell(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->cmds)
		free_cmds(shell->cmds);
	free_path_pipes(shell);
	shell->cmds = NULL;
	shell->tokens = NULL;
	shell->path = NULL;
	shell->pipes = NULL;
	g_sig_pid = 0;
}
