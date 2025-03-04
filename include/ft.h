/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:46:06 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/04 14:24:49 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include "../lib/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

extern pid_t	g_sig_pid;

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
	int				*echo;
	t_redirs		*in;
	t_redirs		*out;
}					t_command;

typedef struct s_token
{
	char			*token;
	bool			echo;
}					t_token;

typedef struct s_shell
{
	char			*input;
	t_token			*tokens;
	char			**env;
	char			**path;
	int				**pipes;
	int				num_cmds;
	int				exit_status;
	pid_t			last_child;
	t_command		*cmds;
}					t_shell;

// Free
void				free_tab(char **tab);
void				free_tokens(t_token *tokens);
void				free_shell(t_shell *shell);

// Parsing
int					count_cmd(char *input);
int					is_redirs(char *token);
bool				check_error(t_shell *shell);
bool				is_whitespace(char c);
bool				is_var(char *arg);
char				*get_env_var(char **env, char *var);
char				*get_prompt(char **env);
void				display_shell(t_shell *shell);
void				get_number_redir(t_token *tokens, int *count, bool in);
void				get_redirs(t_command *cmds, t_token *tokens, int *i);
t_token 			*tokenize(char *input, int *cmd__nums);
t_command			*get_commands(t_token *tokens, int cmd_nums);

// Signal
void				init_signals(void);

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
void				redirect_simple_cmd(t_shell *shell);

// Builtin
void				ft_pwd(void);
void				ft_cd(t_shell *shell, int index);
void				ft_env(t_shell *shell);
void				ft_export(t_shell *shell, char **args);
void				print_export(t_shell *shell);
void				ft_unset(t_shell *shell, char *var);
void				ft_echo(t_shell *shell, char **args, int *echo);
void				ft_exit(t_shell *shell, char **args);
int					handle_builtin(t_shell *shell, int i, int is_child);

// Export Utils
char				*ft_strndup(const char *s, int n);
char				**realloc_env(char **env, int size);
int					is_valid_varname(const char *name);
void				print_export(t_shell *shell);
void				handle_invalid_identifier(t_shell *shell, char *arg);

#endif
