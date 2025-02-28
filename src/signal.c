/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:41:21 by ebigotte          #+#    #+#             */
/*   Updated: 2025/02/28 10:50:51 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	// rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
}

void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
