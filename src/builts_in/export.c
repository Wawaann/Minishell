/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedmarti <cedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:55:52 by cedmarti          #+#    #+#             */
/*   Updated: 2025/02/26 17:28:48 by cedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

char	*ft_strndup(const char *s, int n)
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

char	**realloc_env(char **env, int size)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i] && i < size)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}


void	ft_export(t_shell *shell, char *var)
{
	int		i;
	char	*name;
	char	*equal_pos;

	// Verif format VAR=VALUE
	equal_pos = ft_strchr(var, '=');
	if (!var || !equal_pos)
		return ;

	// Recuperer le nom de la variable pour le chercher dans la liste
	name = ft_strndup(var, equal_pos - var);

	// Si variable existe
		// Supprimer ancienne valeur
		// Mettre nouvelle valeur
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0
			&& shell->env[i][strlen(name)] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(var);
			free(name);
			return ;
		}
		i++;
	}

	// Sinon
		// Aggrandir le tableau de 1
		// Ajouter nouvelle variable et valeur
		// Null termine le tab
	shell->env = realloc_env(shell->env, i + 1);
	shell->env[i] = ft_strdup(var);
	shell->env[i + 1] = NULL;
	free(name);
}
