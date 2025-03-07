/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:33:27 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/07 16:36:41 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*concat_tokens(char *token, char *sub_token)
{
	char	*temp;

	temp = ft_strjoin(token, sub_token);
	free(sub_token);
	free(token);
	return (temp);
}

void	set_echo(char c, bool *echo)
{
	if (c == '\'')
		*echo = false;
	else
		*echo = true;
}

char	*get_var(char *token)
{
	int		len;
	char	*var;

	len = 0;
	while (token[1 + len] && ft_isalnum(token[1 + len]))
		len++;
	var = ft_substr(token, 1, len);
	return (var);
}

bool	is_valid_token(t_shell *shell, int count)
{
	int		i;
	int		valid;
	char	*tmp;
	char	*var;

	i = 0;
	valid = 0;
	while (shell->tokens[count].token[i])
	{
		tmp = ft_strchr(shell->tokens[count].token + i, '$');
		if (!tmp || !*(tmp + 1))
			break ;
		if (ft_strncmp(tmp, "$ ", 2) == 0
			|| ft_strncmp(tmp, "$?", 2) == 0 || ft_strncmp(tmp, "$$", 2) == 0)
			valid++;
		var = get_var(tmp);
		if (get_env_var(shell->env, var))
			valid++;
		free(var);
		i++;
	}
	if (valid == 0 && i > 0)
		return (false);
	return (true);
}

void	set_valid_tokens(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->tokens[i].token)
	{
		shell->tokens[i].valid = true;
		if (shell->tokens[i].echo)
		{
			shell->tokens[i].valid = is_valid_token(shell, i);
			if (shell->tokens[i].valid)
				shell->tokens[i].token = refactor_token(shell, i);
		}
		i++;
	}
}
