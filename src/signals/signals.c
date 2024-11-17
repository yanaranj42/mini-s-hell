/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:21:45 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/17 16:13:12 by yanaranj         ###   ########.fr       */
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
	/* else if (sig == SIGQUIT)
	{	
		rl_replace_line("", 1);
		ft_putstr_fd("Quit (core dumped)\n", 1);
		rl_on_new_line();
		g_error = 131;
	} */
}

void	do_eof()
{
	write(1, "exit\n", 5);
	printf("doing EOF\t");
	printf("[%i]\n", g_error);
	exit(g_error);
}

// REVISAR
void	handle_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		ft_putendl_fd("", 1);
		//rl_on_new_line();
		//rl_redisplay();
		g_error = 42;
	}
}


void	set_sig_default() //si tenemos el NORM puede que no sea necesarios
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	init_signal()
{
	signal(SIGINT, norm_sig_handle);
	signal(SIGQUIT, SIG_IGN);
}

/*si estoy en mitad del executor, CORE DUMP*/