/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:28:51 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/27 12:07:43 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

bool	valide_pipe(char **tokens, int i, int *exit_status)
{
	if (i == 0 && ft_strncmp(tokens[i], "|", 2) == 0)
	{
		printf("syntax error near unexpected token `|'\n");
		*exit_status = 2;
		return (false);
	}
	if (ft_strncmp(tokens[i], "|", 2) == 0 && !tokens[i + 1])
	{
		printf("syntax error near unexpected token `|'\n");
		*exit_status = 2;
		return (false);
	}
	if (ft_strncmp(tokens[i], "|", 2) == 0 && ft_strncmp(tokens[i + 1], "|", 2) == 0)
	{
		printf("syntax error near unexpected token `|'\n");
		*exit_status = 2;
		return (false);
	}
	return (true);
}

bool	validate_redirs(char **tokens, int i, int *exit_status)
{
	if (is_redirs(tokens[i]) && !tokens[i + 1])
	{
		printf("syntax error near unexpected token `newline'\n");
		*exit_status = 2;
		return (false);
	}
	if (is_redirs(tokens[i]) && is_redirs(tokens[i + 1]))
	{
		printf("syntax error near unexpected token `%s'\n", tokens[i + 1]);
		*exit_status = 2;
		return (false);
	}
	return (true);
}

bool	check_error(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->tokens[i])
	{
		if (!valide_pipe(shell->tokens, i, &shell->exit_status))
			return (false);
		if (!validate_redirs(shell->tokens, i, &shell->exit_status))
			return (false);
		i++;
	}
	return (true);
}
