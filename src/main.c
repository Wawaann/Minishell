/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:47:56 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/19 15:20:58 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft.h"

int	main(int ac, char **av, char **env)
{
	char *line;

	while (1)
	{
		line = readline("$> ");
		if (!line)
			return (0);
		if (ft_strncmp(line, "exit", 4) == 0)
			break;
		printf("line: '%s'\n", line);
		add_history(line);
		free(line);
	}
	clear_history();
	return (0);
}
