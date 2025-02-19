/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:46:06 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/19 15:48:25 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include "../lib/include/libft.h"

#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_shell
{
	char	*input;       // Ligne de commande brute (récupérée avec readline)
	char	**tokens;     // Commande découpée en tokens
	char	***cmds;      // Tableau des commandes séparées par `|`
	int		num_cmds;     // Nombre de commandes
	char	**env;        // Environnement
	int		exit_status;  // Dernier code de retour
	int		*operator;		//[< , << , > , >>]
	char	*infile;		// nom fu fichier
	char	*outfile;		// nom du fichier
}			t_shell;

#endif
