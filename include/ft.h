/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:46:06 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/27 14:20:24 by cedmarti         ###   ########.fr       */
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
bool				check_error(t_shell *shell);
char				**tokenize(char *input, int *num_cmds);
void				get_number_redir(char **tokens, int *count, bool in);
void				get_redirs(t_command *cmds, char **tokens, int *i);
t_command			*get_commands(char **tokens, int cmd_nums);

// Exec
void				ft_error(char *str);
void				execute_simple_cmd(t_shell *shell);
void				execute_command(t_shell *shell);

// Handle_heredoc
void				collect_all_heredocs(t_shell *shell);
void				redirect_heredoc(t_shell *shell, int index);
void				cleanup_heredocs(t_shell *shell);

// Handle_pipes
void				init_pipes(t_shell *shell);
void				redirect_pipes(t_shell *shell, int index);
void				ft_wait_childs(t_shell *shell);
void				ft_close_pipes(t_shell *shell);

// Handle_redir
void				redirect_outfiles(t_shell *shell, int index);
void				redirect_infiles(t_shell *shell, int index);

// Exec Utils
char				**get_all_path(t_shell *shell);
char				*get_path(t_shell *shell, char *cmd_name);
void				init_path(t_shell *shell);

// Builtin
void				ft_pwd(void);
void				ft_cd(t_shell *shell, int index);
void				ft_env(t_shell *shell);
void				ft_export(t_shell *shell, char *var);
void				ft_unset(t_shell *shell, char *var);
void				ft_exit(t_shell *shell);

#endif
