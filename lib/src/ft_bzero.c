/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:52:28 by ebigotte          #+#    #+#             */
/*   Updated: 2025/05/05 10:40:07 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_bzero(void *ptr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
}
