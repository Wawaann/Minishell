/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:55:52 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/28 14:21:57 by cedmarti         ###   ########.fr       */
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
	int i;

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


void	ft_export(t_shell *shell, char *var)
{
	int		i;
	char	*name;
	char	*equal_pos;

	equal_pos = ft_strchr(var, '=');
	if (equal_pos)
		name = ft_strndup(var, equal_pos - var);
	else
		name = ft_strdup(var);

	if (!is_valid_varname(name))
	{
		ft_putstr_fd("export: not a valid identifier\n", 2);
		free(name);
		shell->exit_status = 1;
		return ;
	}
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0 &&
			(shell->env[i][ft_strlen(name)] == '='
			|| shell->env[i][ft_strlen(name)] == '\0'))
		{
			if (equal_pos)
			{
				free(shell->env[i]);
				shell->env[i] = ft_strdup(var);
			}
			free(name);
			return ;
		}
		i++;
	}
	shell->env = realloc_env(shell->env, i + 1);
	shell->env[i] = ft_strdup(var);
	shell->env[i + 1] = NULL;
	free(name);
	shell->exit_status = 0;
}
