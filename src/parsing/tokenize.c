/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:47:00 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/07 16:27:51 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*expand_variable(t_shell *shell, char *token)
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
	var_value = get_env_var(shell->env, var_name);
	free(var_name);
	if (!var_value)
		return (token);
	expanded = gnl_strjoin(ft_substr(token, 0, start - token), var_value);
	expanded = gnl_strjoin(expanded, start + var_len + 1);
	free(token);
	return (expanded);
}

static char	*handle_quotes(t_shell *shell, int *i, char *token)
{
	int		start;
	char	quote;
	char	*sub_token;

	quote = shell->input[*i];
	(*i)++;
	start = *i;
	while (shell->input[*i] && shell->input[*i] != quote)
		(*i)++;
	sub_token = ft_substr(shell->input, start, *i - start);
	if (quote == '"')
		sub_token = expand_variable(shell, sub_token);
	token = concat_tokens(token, sub_token);
	if (shell->input[*i] == quote)
		(*i)++;
	return (token);
}

static char	*extract_token(t_shell *shell, int *i, int count)
{
	int		start;
	char	*token;
	char	*sub_token;

	token = ft_strdup("");
	set_echo(shell->input[*i], &shell->tokens[count].echo);
	while (shell->input[*i])
	{
		if (shell->input[*i] == '"' || shell->input[*i] == '\'')
			token = handle_quotes(shell, i, token);
		else if (shell->input[*i] == ' ' || is_sep(shell->input[*i]))
			break ;
		else
		{
			start = *i;
			while (shell->input[*i] && shell->input[*i] != ' '
				&& shell->input[*i] != '"' && shell->input[*i] != '\''
				&& !is_sep(shell->input[*i]))
				(*i)++;
			sub_token = ft_substr(shell->input, start, *i - start);
			sub_token = expand_variable(shell, sub_token);
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

void	tokenize(t_shell *shell)
{
	int		i;
	int		count;
	char	*token;

	i = 0;
	count = 0;
	shell->tokens = ft_calloc(100, sizeof(t_token));
	shell->num_cmds = count_cmd(shell->input);
	while (shell->input[i])
	{
		while (shell->input[i] && shell->input[i] == ' ')
			i++;
		if (!shell->input[i])
			break ;
		if (is_sep(shell->input[i]))
			token = extract_operator(shell->input, &i);
		else
			token = extract_token(shell, &i, count);
		if (token)
			shell->tokens[count++].token = token;
	}
	shell->tokens[count].token = NULL;
	set_valid_tokens(shell);
}
