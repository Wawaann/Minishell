/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:54:40 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/04 19:38:42 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	count_cmd(char *input)
{
	int	i;
	int	count;
	int	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			quote = !quote;
		if (input[i] == '|' && !quote)
			count++;
		i++;
	}
	return (count + 1);
}

void	display_redirs(t_redirs *redirs, int count)
{
	int	i;

	i = 0;
	if (count == 0)
		printf("None");
	while (i < count)
	{
		printf("[%d: %s] ", redirs[i].type, redirs[i].file);
		i++;
	}
	printf("\n");
}

void	display_cmds(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (i < shell->num_cmds)
	{
		printf("\tCommand %d: {\n", i);
		printf("\t\tNumber of Args: %d\n", (int)ft_tablen(shell->cmds[i].args));
		printf("\t\tArgs: ");
		j = 0;
		while (shell->cmds[i].args[j])
		{
			printf("[%s] ", shell->cmds[i].args[j]);
			j++;
		}
		printf("\n");
		printf("\t\tNumber of redir In: %d, Out: %d, All: %d\n",
			shell->cmds[i].in, shell->cmds[i].out, shell->cmds[i].count);
		printf("\t\tAll redirs: ");
		display_redirs(shell->cmds[i].redirs, shell->cmds[i].count);
		printf("\t}\n");
		i++;
	}
}

void	display_shell(t_shell *shell)
{
	int	i;

	i = 0;
	printf("Input: {%s}\n", shell->input);
	printf("Tokens: ");
	while (shell->tokens[i].token)
	{
		printf("[\"%s\" -> %d] ", shell->tokens[i].token,
			shell->tokens[i].echo);
		i++;
	}
	printf("\n");
	printf("Number of commands: %d\n", shell->num_cmds);
	printf("Commands: {\n");
	display_cmds(shell);
	printf("}\n--------------------\n");
}
