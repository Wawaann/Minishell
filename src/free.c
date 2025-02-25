/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:00:37 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/25 15:31:12 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

void	free_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->num_cmds - 1)
	{
		free(shell->pipes[i]);
		i++;
	}
	free(shell->pipes);
}

void	free_path(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->num_cmds)
	{
		if (shell->path[i])
			free(shell->path[i]);
		i++;
	}
	free(shell->path);
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
		i++;
	}
	free(cmds);
}

void	free_shell(t_shell *shell)
{
	free(shell->input);
	free_tokens(shell->tokens);
	free_cmds(shell->cmds);
	if (shell->path)
		free_path(shell);
	if (shell->pipes)
		free_pipes(shell);
}
