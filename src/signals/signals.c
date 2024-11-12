/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:21:45 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/12 16:52:43 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		g_error = 0;

void	norm_sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_error = 130;
	}
}

void	do_eof(t_general *data)
{
	(void)data;
	write(1, "exit\n", 5);
	printf("doing EOF\t");
	printf("[%i]\n", g_error);
	exit(g_error);
}

// REVISAR
void	norm_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_replace_line("", 1);
		g_error = 130;
	}
}
