/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:21:45 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/19 20:27:09 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int g_error = 0;

void	control_c_heredoc_handler(int sig) //for bloquing cntrl-c
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		write(2, "\n", 1);
		exit (130);
	}
}

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
	printf(PURPLE"    The night is dark and full of secrets 🌜 ✨\n\n"END);
	printf("exit\n");
	exit(g_error);
}

void	init_non_bloquing_signals()
{
	if (g_error != 0)
		g_error = 0;
	signal(SIGINT, control_c_normal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_heredoc_signals()
{
	signal(SIGINT, control_c_heredoc_handler); // control c
	signal(SIGQUIT, SIG_IGN); // control contrabarra

}

void	init_bloquing_signals()
{
	signal(SIGINT, SIG_DFL); // control c
	signal(SIGQUIT, SIG_DFL); // control contrabarra
}

void	init_ignore_signals ()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
