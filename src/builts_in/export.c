/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:55:52 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/03 15:02:13 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

static char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*dup;

	i = 0;
	while (s[i] && i < n)
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	**realloc_env(char **env, int size)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i] && i < size)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	free_tokens(env);
	return (new_env);
}

int	is_valid_varname(const char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		printf("declare -x ");
		printf("%s\n", shell->env[i]);
		i++;
	}
}

void	add_update_env(t_shell *shell, char *var, char *name, char *has_value)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0
			&& (shell->env[i][ft_strlen(name)] == '='
			|| shell->env[i][ft_strlen(name)] == '\0'))
		{
			if (has_value)
			{
				free(shell->env[i]);
				shell->env[i] = ft_strdup(var);
			}
			return ;
		}
		i++;
	}
	shell->env = realloc_env(shell->env, i + 1);
	shell->env[i] = ft_strdup(var);
	shell->env[i + 1] = NULL;
}

void	ft_export(t_shell *shell, char **args)
{
	int		i;
	char	*name;
	char	*equal_pos;

	if (!args[1])
	{
		print_export(shell);
		shell->exit_status = 0;
		return ;
	}
	i = 1;
	while (args[i])
	{
		equal_pos = ft_strchr(args[i], '=');
		if (equal_pos)
			name = ft_strndup(args[i], equal_pos - args[i]);
		else
			name = ft_strdup(args[i]);
		if (!is_valid_varname(name))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			shell->exit_status = 1;
		}
		else
			add_update_env(shell, args[i], name, equal_pos);
		free(name);
		i++;
	}
}
