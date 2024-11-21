/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_messages.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:05:12 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/21 19:04:29 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	maximum_heredoc_exceeded(void)
{
	write(2, RED, ft_strlen(RED));
	write(2, "💀 minishell: ", 16);
	write(2, ": maximum here-document count exceeded\n", 39);
	write(2, END, ft_strlen(END));
}

void	unexpected_token_message(char *message)
{
	write(2, RED, ft_strlen(RED));
	write(2, "💀 minishell: ", 16);
	write(2, "syntax error near unexpected token\n", 35);
	write(2, message, ft_strlen(message));
	write(2, END, ft_strlen(END));
	write(2, "\n", 1);
}
