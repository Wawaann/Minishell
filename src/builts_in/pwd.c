/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:34:31 by cedmarti          #+#    #+#             */
/*   Updated: 2025/03/10 14:54:54 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	ft_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_putstr_fd("Error with pwd\n", 2);
	printf("%s\n", cwd);
	free(cwd);
	shell->exit_status = 0;
}
