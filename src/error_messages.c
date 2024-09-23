/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:05:12 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/14 15:23:56 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "minishell.h"

void	no_such_file_or_directory(char *start)
{
	write(2, RED, ft_strlen(RED)); // BORRAR
	write(2, "💀 bash: ", 11);
	write(2, start, ft_strlen(start));
	write(2, ": No such FILE_REDIRECTION or directory", 27);
	write(2, END, ft_strlen(END)); // BORRAR
	write(2, "\n", 1);
	exit(127);
}

void	permission_denied(char *start)
{
	write(2, RED, ft_strlen(RED)); // BORRAR
	write(2, "💀 bash: ", 11);
	write(2, "Permission denied: ", 19);
	write(2, start, ft_strlen(start));
	write(2, END, ft_strlen(END)); // BORRAR
	write(2, "\n", 1);
	exit(126);
}

void	command_not_found(char *start)
{
	write(2, RED, ft_strlen(RED)); // BORRAR
	write(2, "💀 bash: ", 11);
	write(2, "Command not found: ", 19);
	write(2, start, ft_strlen(start));
	write(2, END, ft_strlen(END)); // BORRAR
	write(2, "\n", 1);
	exit(127);
}

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