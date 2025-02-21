/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:46:06 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/21 13:41:47 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include "../lib/include/libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef struct s_redirection
{
	char			*file;		// Fichier d'entrée
	int				type;		// Type de redirection
}			t_redirection;

typedef struct s_command
{
	char			**args;		// Arguments de la commande
	t_redirection	*in;		// Redirections infile
	t_redirection	*out;		// Redirections outfile
}			t_command;

typedef struct s_shell
{
	char		*input;         // Ligne de commande brute (récupérée avec readline)
	char		**tokens;       // Commande découpée en tokens
	char		**env;          // Environnement
	char		**path;			// Chemin(s) vers la/les commande(s) (si plusieurs pipes, plusieurs chemins)
	int			**pipes;		// double tab de pipes ({0 , 1} {2 , 3} ...) index 0 (0, 2)= lecture et index 1 (1, 3)= ecriture
	int			num_cmds;       // Nombre de commandes
	int			exit_status;    // Dernier code de retour
	t_command	*cmds;          // Tableau de commandes
}			t_shell;

// Free
void	free_double_tab(char **tab);
void	free_pipes(t_shell *shell);
void	free_cmds(t_shell *shell);
void	free_path(t_shell *shell);
void	free_all(t_shell *shell);

// Exec
void	ft_error(char *str);
void	execute_simple_cmd(t_shell *shell);
void	execute_command(t_shell *shell);

// Exec Utils
char	**get_all_path(t_shell *shell);
char	*get_path(t_shell *shell, char *cmd_name);
void	init_path(t_shell *shell);
void	init_pipes(t_shell *shell);
void	ft_close_pipes(t_shell *shell);
void	ft_wait_childs(t_shell *shell);

#endif
