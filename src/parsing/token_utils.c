/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebigotte <ebigotte@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:33:27 by ebigotte          #+#    #+#             */
/*   Updated: 2025/03/04 15:35:22 by ebigotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*concat_tokens(char *token, char *sub_token)
{
	char	*temp;

	temp = ft_strjoin(token, sub_token);
	free(sub_token);
	free(token);
	return (temp);
}
