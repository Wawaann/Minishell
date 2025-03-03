/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:31:21 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/03 17:26:27 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void print_env_var(t_shell *shell, const char *var)
{
    char *value;

	if (var[0] == '\0' || var[0] == ' ')
	{
		printf("$");
		return ;
	}
	if (var[0] == '?')
	{
		printf("%d", shell->exit_status);
		if (var[1] != '\0')
			printf("%s", &var[1]);
		return ;
	}
	value = getenv(var);
    if (value)
        printf("%s", value);
}

void print_argument(t_shell *shell, const char *arg)
{
    int i = 0;
	int start;
    bool in_double_quote = false;
    bool in_single_quote = false;

    while (arg[i])
    {
        if (arg[i] == '"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else if (arg[i] == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
        else if (arg[i] == '$' && !in_single_quote) // Gestion de $VAR
        {
            start = ++i;
            while (arg[i] && (arg[i] != ' ' && arg[i] != '"' && arg[i] != '\''))
                i++;
            char *var = ft_strndup(&arg[start], i - start);
            print_env_var(shell, var);
            free(var);
            i--;
        }
        else
            printf("%c", arg[i]);
        i++;
    }
}

void ft_echo(t_shell *shell, char **args)
{
    bool	newline;
    int		i;

	i = 1;
	newline = true;
    if (args[i] && strcmp(args[i], "-n") == 0)
    {
        newline = false;
        i++;
    }
    while (args[i])
    {
        print_argument(shell, args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
}

