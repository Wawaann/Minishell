/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:46:06 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/25 15:43:40 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_H
# define FT_H

# include "../lib/include/libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef struct s_redirs
{
	char			*file;
	int				type;
}					t_redirs;

// Type de redirection [1: <, 2: <<, 3: >, 4: >>]

typedef struct s_command
{
	char			**args;
	int				in_count;
	int				out_count;
	t_redirs		*in;
	t_redirs		*out;
}					t_command;

typedef struct s_shell
{
	char			*input;
	char			**tokens;
	char			**env;
	char			**path;
	int				**pipes;
	int				num_cmds;
	int				exit_status;
	t_command		*cmds;
}					t_shell;

// Free
void				free_tokens(char **tokens);
void				free_shell(t_shell *shell);

// Parsing
int					count_cmd(char *input);
int					is_redirs(char *token);
char				**tokenize(char *input, int *num_cmds);
void				get_number_redir(char **tokens, int *count, bool in);
void				get_redirs(t_command *cmds, char **tokens, int *i);
t_command			*get_commands(char **tokens, int cmd_nums);

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
