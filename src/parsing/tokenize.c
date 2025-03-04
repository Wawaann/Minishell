/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:47:00 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/04 15:00:27 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

// static bool	is_sep(char c)
// {
// 	return (c == '|' || c == '<' || c == '>');
// }

// void	get_quote(char *input, int *i)
// {
// 	int	simple;
// 	int	qdouble;

// 	simple = 0;
// 	qdouble = 0;
// 	while (input[*i])
// 	{
// 		if (input[*i] == '\'' && !qdouble)
// 			simple = !simple;
// 		if (input[*i] == '"' && !simple)
// 			qdouble = !qdouble;
// 		if (input[*i] == ' ' && !simple && !qdouble)
// 			break ;
// 		(*i)++;
// 	}
// }

// char	*extract_token(char *input, int *i)
// {
// 	int		start;

// 	start = *i;
// 	if (input[*i + 1] && input[*i] == '"' && input[*i + 1] != '"')
// 	{
// 		(*i)++;
// 		while (input[*i] && input[*i] != '"')
// 			(*i)++;
// 		if (input[*i] == '"')
// 			(*i)++;
// 	}
// 	else
// 	{
// 		get_quote(input, i);
// 	}
// 	return (ft_substr(input, start, *i - start));
// }

// char	*extract_operator(char *input, int *i)
// {
// 	int	start;

// 	start = *i;
// 	if ((input[*i] == '<' && input[*i + 1] == '<')
// 		|| (input[*i] == '>' && input[*i + 1] == '>'))
// 		(*i) += 2;
// 	else
// 		(*i)++;
// 	return (ft_substr(input, start, *i - start));
// }

// char	**tokenize(char *input, int *cmd_nums)
// {
// 	int		i;
// 	int		count;
// 	char	*token;
// 	char	**tokens;

// 	i = 0;
// 	count = 0;
// 	tokens = ft_calloc(100, sizeof(char *));
// 	(*cmd_nums) = count_cmd(input);
// 	while (input[i])
// 	{
// 		while (input[i] && is_whitespace(input[i]))
// 			i++;
// 		if (!input[i])
// 			break ;
// 		if (is_sep(input[i]))
// 			token = extract_operator(input, &i);
// 		else
// 			token = extract_token(input, &i);
// 		if (token)
// 			tokens[count++] = token;
// 	}
// 	tokens[count] = NULL;
// 	return (tokens);
// }

// static bool	is_sep(char c)
// {
// 	return (c == '|' || c == '<' || c == '>');
// }

// /**
//  * Cette fonction extrait un token en prenant en compte les guillemets.
//  * Elle fusionne les guillemets consécutifs.
//  */
// char	*extract_token(char *input, int *i)
// {
// 	int		start;
// 	char	quote;
// 	char	*token;
// 	char	*sub_token;
// 	char	*temp;

// 	start = *i;
// 	quote = 0;
// 	token = ft_strdup("");  // Stockage du token final

// 	while (input[*i])
// 	{
// 		// Si on tombe sur un guillemet, on entre dans une section quote
// 		if (input[*i] == '"' || input[*i] == '\'')
// 		{
// 			quote = input[*i]; // On mémorise le type de quote
// 			(*i)++; // On avance pour ignorer ce premier guillemet

// 			// On capture tout jusqu'à la fermeture du même type de guillemet
// 			start = *i;
// 			while (input[*i] && input[*i] != quote)
// 				(*i)++;
// 			sub_token = ft_substr(input, start, *i - start);

// 			// On concatène le contenu entre guillemets avec le token actuel
// 			temp = ft_strjoin(token, sub_token);
// 			free(sub_token);
// 			free(token);
// 			token = temp;

// 			// On avance pour ignorer le guillemet de fermeture
// 			if (input[*i] == quote)
// 				(*i)++;
// 		}
// 		// Si on rencontre un espace en dehors des quotes, on termine le token
// 		else if (input[*i] == ' ' || is_sep(input[*i]))
// 			break;
// 		else
// 		{
// 			// Ajout d'un caractère normal au token
// 			start = *i;
// 			while (input[*i] && input[*i] != ' ' && input[*i] != '"' && input[*i] != '\'' && !is_sep(input[*i]))
// 				(*i)++;
// 			sub_token = ft_substr(input, start, *i - start);

// 			temp = ft_strjoin(token, sub_token);
// 			free(sub_token);
// 			free(token);
// 			token = temp;
// 		}
// 	}

// 	return (token);
// }

// /**
//  * Cette fonction extrait les opérateurs de redirection ('<', '<<', '>', '>>')
//  */
// char	*extract_operator(char *input, int *i)
// {
// 	int	start;

// 	start = *i;
// 	if ((input[*i] == '<' && input[*i + 1] == '<')
// 		|| (input[*i] == '>' && input[*i + 1] == '>'))
// 		(*i) += 2;
// 	else
// 		(*i)++;
// 	return (ft_substr(input, start, *i - start));
// }

// /**
//  * Fonction principale de tokenization
//  */
// char	**tokenize(char *input, int *cmd_nums)
// {
// 	int		i;
// 	int		count;
// 	char	*token;
// 	char	**tokens;

// 	i = 0;
// 	count = 0;
// 	tokens = ft_calloc(100, sizeof(char *));
// 	(*cmd_nums) = count_cmd(input);
// 	while (input[i])
// 	{
// 		while (input[i] && input[i] == ' ')
// 			i++;
// 		if (!input[i])
// 			break;
// 		if (is_sep(input[i]))
// 			token = extract_operator(input, &i);
// 		else
// 			token = extract_token(input, &i);
// 		if (token)
// 			tokens[count++] = token;
// 	}
// 	tokens[count] = NULL;
// 	return (tokens);
// }

static bool	is_sep(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static char	*concat_tokens(char *token, char *sub_token)
{
	char	*temp;

	temp = ft_strjoin(token, sub_token);
	free(sub_token);
	free(token);
	return (temp);
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
			while (input[*i] && input[*i] != ' ' && input[*i] != '"' &&
				input[*i] != '\'' && !is_sep(input[*i]))
				(*i)++;
			sub_token = ft_substr(input, start, *i - start);
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

t_token *tokenize(char *input, int *cmd__nums)
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
	return (tokens);
}
