/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:05:12 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/12 15:50:49 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "minishell.h"

// void	permission_denied(char *start)
// {
// 	printf("%s", "Permission denied: ");
// 	exit(126);
// }

// void	command_not_found(char *start)
// {
// 	printf("%s", "Command not found: ");
// 	exit(127);
// }

void	perror_message(char *start, char *message)
{
	if (start)
		printf("%s: ", start); 
	perror(message);
}