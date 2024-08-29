/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:05:12 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/29 13:50:28 by mfontser         ###   ########.fr       */
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

void	unexpected_token_message(char *message)
{
	write(2, RED, ft_strlen(RED));
	write(2, "💀 bash: ", 11);
	write(2, END, ft_strlen(END));
	write(2, "syntax error near unexpected token ", 35);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);

	//BORRAR:
	write(2, "\n", 1);
	write(2, GREEN, ft_strlen(GREEN));
	write(2, "******************* FREE *******************\n", 45);
	write(2, END, ft_strlen(END));
}

void	perror_message(char *start, char *message)
{
	if (start)
	{
		write(2, RED, ft_strlen(RED));
		write(2, start, ft_strlen(start));
		write(2, ": ", 2);
		write(2, END, ft_strlen(END));
	}
	perror(message);
}