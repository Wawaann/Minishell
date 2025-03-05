/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:33:27 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/05 17:48:34 by ebigotte         ###   ########.fr       */
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

char	*expand_variable(char *token)
{
	char	*expanded;
	char	*start;
	char	*var_name;
	char	*var_value;
	int		var_len;

	start = ft_strchr(token, '$');
	if (!start || !*(start + 1))
		return (token);
	var_len = 0;
	while (start[1 + var_len] && (ft_isalnum(start[1 + var_len])
			|| start[1 + var_len] == '_'))
		var_len++;
	var_name = ft_substr(start, 1, var_len);
	var_value = getenv(var_name);
	free(var_name);
	if (!var_value)
		return (token);
	expanded = ft_strjoin(ft_substr(token, 0, start - token), var_value);
	expanded = ft_strjoin(expanded, start + var_len + 1);
	free(token);
	return (expanded);
}

void	set_valid_tokens(t_token *tokens)
{
	int		i;
	int		len;
	char	*tmp;
	char	*var;

	i = 0;
	while (tokens[i].token)
	{
		tokens[i].valid = true;
		tmp = ft_strchr(tokens[i].token, '$');
		if (!tmp || !*(tmp + 1) || strncmp(tmp, "$ ", 2) == 0
			|| strncmp(tmp, "$?", 2) == 0 || strncmp(tmp, "$$", 2) == 0)
		{
			i++;
			continue ;
		}
		len = 0;
		while (tmp[1 + len] && ft_isalnum(tmp[1 + len]))
			len++;
		var = ft_substr(tmp, 1, len);
		if (!getenv(var))
			tokens[i].valid = false;
		free(var);
		i++;
	}
}
