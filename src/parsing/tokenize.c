/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:47:00 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/01 16:00:29 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static bool	is_sep(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	get_quote(char *input, int *i)
{
	int	quote;

	quote = 0;
	while (input[*i])
	{
		if ((input[*i] == '"' || input[*i] == '\'') && quote == 0)
			quote = 1;
		else if ((input[*i] == '"' || input[*i] == '\'') && quote == 1)
			quote = 0;
		if (is_sep(input[*i]))
			break ;
		if (is_whitespace(input[*i]) && quote == 0)
			break ;
		(*i)++;
	}
}

char	*extract_token(char *input, int *i)
{
	int		start;

	start = *i;
	if (input[*i + 1] && input[*i] == '"' && input[*i + 1] != '"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '"')
			(*i)++;
		if (input[*i] == '"')
			(*i)++;
	}
	else
	{
		get_quote(input, i);
	}
	return (ft_substr(input, start, *i - start));
}

char	*extract_operator(char *input, int *i)
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

char	**tokenize(char *input, int *cmd_nums)
{
	int		i;
	int		count;
	char	*token;
	char	**tokens;

	i = 0;
	count = 0;
	tokens = ft_calloc(100, sizeof(char *));
	(*cmd_nums) = count_cmd(input);
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_sep(input[i]))
			token = extract_operator(input, &i);
		else
			token = extract_token(input, &i);
		if (token)
			tokens[count++] = token;
	}
	tokens[count] = NULL;
	return (tokens);
}
