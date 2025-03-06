/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:47:00 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/05 17:48:39 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static bool	is_sep(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*handle_quotes(char *input, int *i, char quote, char *token)
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
	set_echo(input[*i], echo);
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
