/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:47:56 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/23 11:28:33 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

void    init_shell(t_shell *shell, char **env)
{
    shell->input = NULL;
    shell->tokens = NULL;
    shell->cmds = NULL;
    shell->num_cmds = 0;
    shell->env = env;
    shell->exit_status = 0;
}

char    **tokenize(char *input, int *num_cmds)
{
    char    **tokens;
    int     i;

    tokens = ft_split(input, " \t");
    i = 0;
	(*num_cmds) = 0;
    while (tokens[i])
    {
        if (ft_strncmp(tokens[i], "|", 1) == 0)
        {
            (*num_cmds)++;
        }
        i++;
    }
    (*num_cmds)++;
    return (tokens);
}

void    display_shell(t_shell *shell)
{
    printf("input: %s\n", shell->input);
    printf("tokens: ");
    for (int i = 0; shell->tokens[i]; i++)
        printf("[%s] ", shell->tokens[i]);
    printf("\n");
    printf("num_cmds: %d\n", shell->num_cmds);
}

int main(int ac, char **av, char **env)
{
    t_shell shell;

    (void)av;
    if (ac != 1)
        return (0);
    init_shell(&shell, env);
    while (1)
    {
        shell.input = readline("$> ");
        if (!shell.input || ft_strncmp(shell.input, "exit", 4) == 0)
            break;
        add_history(shell.input);
        shell.tokens = tokenize(shell.input, &shell.num_cmds);
        shell.cmds = get_commands(shell.tokens, shell.num_cmds);
        display_shell(&shell);
        free(shell.input);
    }
    clear_history();
    return (0);
}
