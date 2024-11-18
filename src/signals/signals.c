/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:21:45 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/17 07:29:45 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		g_error = 0;

void	control_c_normal_handler(int sig) //for cntrl-c
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

void	do_eof()
{
	write(1, "exit\n", 5);
	printf("doing EOF\t");
	printf("[%i]\n", g_error);
	exit(g_error);
}


void	set_sig_default()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// REVISAR
// void	handle_sig_heredoc(int sig) //for cntrl-c in heredock
// {
// 	if (sig == SIGINT)
// 	{
// 		rl_replace_line("", 1);
// 		rl_on_new_line();
// 		write(2, "\n", 1);
// 		g_global = 130;
// 		//rl_redisplay();
// 		exit (130);
// 	}
// }

void	init_non_bloquing_signals()
{
	signal(SIGINT, control_c_normal_handler);
	signal(SIGQUIT, SIG_IGN);
}

