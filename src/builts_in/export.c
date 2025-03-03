/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:55:52 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/03 17:01:52 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

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
			handle_invalid_identifier(shell, args[i]);
		else
			add_update_env(shell, args[i], name, equal_pos);
		free(name);
		i++;
	}
}
