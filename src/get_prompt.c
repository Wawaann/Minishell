/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:31:58 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/28 16:47:41 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*get_env_var(char **env, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (NULL);
}

void	extract_prompt(char **prompt, char **tab)
{
	int		i;
	char	*tmp;

	i = ft_tablen(tab) - 4;
	if (i < 0)
		i = 0;
	while (tab[i])
	{
		tmp = *prompt;
		*prompt = ft_strjoin(*prompt, tab[i]);
		free(tmp);
		if (tab[i + 1])
		{
			tmp = *prompt;
			*prompt = ft_strjoin(*prompt, "/");
			free(tmp);
		}
		i++;
	}
	tmp = *prompt;
	*prompt = ft_strjoin(*prompt, " \033[0;32m$>\033[0m ");
	free(tmp);
}

char	*get_prompt(char **env)
{
	char	*prompt;
	char	*var;
	char	**tab;

	var = get_env_var(env, "PWD");
	tab = ft_split(var, "/");
	prompt = ft_strdup("\033[0;36m\033[1m~/");
	extract_prompt(&prompt, tab);
	free_tokens(tab);
	free(var);
	return (prompt);
}
