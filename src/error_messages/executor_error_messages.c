/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_error_messages.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:05:12 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/22 14:38:46 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	no_such_file_or_directory(char *start)
{
	write(2, RED, ft_strlen(RED));
	write(2, "💀 minishell: ", 16);
	write(2, start, ft_strlen(start));
	write(2, ": No such file or directory", 27);
	write(2, END, ft_strlen(END));
	write(2, "\n", 1);
	exit(127);
}

void	permission_denied(char *start)
{
	write(2, RED, ft_strlen(RED));
	write(2, "💀 minishell: ", 16);
	write(2, start, ft_strlen(start));
	write(2, ": Permission denied", 19);
	write(2, END, ft_strlen(END));
	write(2, "\n", 1);
	exit(126);
}

void	command_not_found(char *start)
{
	write(2, RED, ft_strlen(RED));
	write(2, "💀 minishell: ", 16);
	write(2, start, ft_strlen(start));
	write(2, ": Command not found", 19);
	write(2, END, ft_strlen(END));
	write(2, "\n", 1);
	exit(127);
}

void	perror_message(char *start, char *message)
{
	if (start)
	{
		write(2, RED, ft_strlen(RED));
		write(2, "💀 minishell: ", 16);
		write(2, start, ft_strlen(start));
		write(2, ": ", 2);
		write(2, END, ft_strlen(END));
	}
	perror(message);
}

void	ambiguous_redirect(char *start)
{
	write(2, RED, ft_strlen(RED));
	write(2, "💀 minishell: ", 16);
	write(2, start, ft_strlen(start));
	write(2, ": ambiguous redirect", 20);
	write(2, END, ft_strlen(END));
}
