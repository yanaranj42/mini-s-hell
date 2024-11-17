/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_error_messages.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 04:33:57 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/17 05:08:40 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	end_of_file_in_heredoc(char *limitter_word)
{
	write(2, RED, ft_strlen(RED));
	write(2, "💀 bash: ", 11);
	write(2, "warning: here-document at line 1 delimited by end-of-file", 57);
	write(2, " (wanted `", 10);
	write(2, limitter_word, ft_strlen(limitter_word));
	write(2, "')", 2);
	write(2, END, ft_strlen(END));
	write(2, "\n", 1);
}
