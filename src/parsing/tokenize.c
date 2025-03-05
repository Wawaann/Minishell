/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:47:00 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/05 17:14:07 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static bool	is_sep(char c)
{
	return (c == '|' || c == '<' || c == '>');
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

static char	*handle_quotes(char *input, int *i, char quote, char *token)
{
	int		start;
	char	*sub_token;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	sub_token = ft_substr(input, start, *i - start);
	if (quote == '"')
		sub_token = expand_variable(sub_token);
	token = concat_tokens(token, sub_token);
	if (input[*i] == quote)
		(*i)++;
	return (token);
}

static char	*extract_token(char *input, int *i, bool *echo)
{
	int		start;
	char	*token;
	char	*sub_token;

	token = ft_strdup("");
	if (input[*i] == '\'')
		*echo = false;
	else
		*echo = true;
	while (input[*i])
	{
		if (input[*i] == '"' || input[*i] == '\'')
			token = handle_quotes(input, i, input[*i], token);
		else if (input[*i] == ' ' || is_sep(input[*i]))
			break ;
		else
		{
			start = *i;
			while (input[*i] && input[*i] != ' ' && input[*i] != '"'
				&& input[*i] != '\'' && !is_sep(input[*i]))
				(*i)++;
			sub_token = ft_substr(input, start, *i - start);
			sub_token = expand_variable(sub_token);
			token = concat_tokens(token, sub_token);
		}
	}
	return (token);
}

static char	*extract_operator(char *input, int *i)
{
	int	start;

	start = *i;
	if ((input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>'))
		(*i) += 2;
	else
		(*i)++;
	return (ft_substr(input, start, *i - start));
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

t_token	*tokenize(char *input, int *cmd__nums)
{
	int		i;
	int		count;
	char	*token;
	t_token	*tokens;

	i = 0;
	count = 0;
	tokens = ft_calloc(100, sizeof(t_token));
	(*cmd__nums) = count_cmd(input);
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		if (is_sep(input[i]))
			token = extract_operator(input, &i);
		else
			token = extract_token(input, &i, &tokens[count].echo);
		if (token)
			tokens[count++].token = token;
	}
	tokens[count].token = NULL;
	set_valid_tokens(tokens);
	return (tokens);
}
