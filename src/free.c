/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:44:21 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/21 12:58:40 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void	free_double_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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

void	free_cmds(t_shell *shell)
{
	int	i;
	int	j;

	if (!shell->cmds)
		return;

	i = 0;
	while (i < shell->num_cmds)
	{
		// Libération des arguments
		if (shell->cmds[i].args)
		{
			j = 0;
			while (shell->cmds[i].args[j])
			{
				free(shell->cmds[i].args[j]);
				j++;
			}
			free(shell->cmds[i].args);
		}

		// Libération de la redirection d'entrée
		if (shell->cmds[i].in)
		{
			free(shell->cmds[i].in->file);
			free(shell->cmds[i].in);
		}

		// Libération de la redirection de sortie
		if (shell->cmds[i].out)
		{
			free(shell->cmds[i].out->file);
			free(shell->cmds[i].out);
		}

		i++;
	}
	// Libération du tableau de commandes
	free(shell->cmds);
	shell->cmds = NULL;
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

void	free_all(t_shell *shell)
{
	if (shell->cmds)
		free_cmds(shell);
	if (shell->path)
		free_path(shell);
	if (shell->pipes)
		free_pipes(shell);
}
