/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:46:06 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/21 11:50:29 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include "../lib/include/libft.h"

#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_redirection
{
    char            *file;      // Fichier d'entrée
    int             type;       // Type de redirection
}           t_redirection;

typedef struct s_command
{
    char            **args;     // Arguments de la commande
    t_redirection   *in;        // Redirections infile
    t_redirection   *out;       // Redirections outfile
}           t_command;

typedef struct s_shell
{
    char        *input;         // Ligne de commande brute (récupérée avec readline)
    char        **tokens;       // Commande découpée en tokens
    char        **env;          // Environnement
    int         num_cmds;       // Nombre de commandes
    int         exit_status;    // Dernier code de retour
    t_command   *cmds;          // Tableau de commandes
}           t_shell;

#endif
