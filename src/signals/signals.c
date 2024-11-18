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

void	norm_sig_handle(int sig) //for cntrl-c
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
void	handle_sig_heredoc(int sig) //for cntrl-c in heredock
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		write(2, "\n", 1);
		g_global = 130;
		//rl_redisplay();
		exit (130);
	}
}

void	init_signal()
{
	signal(SIGINT, norm_sig_handle);
	signal(SIGQUIT, SIG_IGN);
}

















void	signal_handle(int status) // to update exit_value after performing simple command
{
	if (WIFEXITED(status)) //returns true if child exited normally with exit;
		g_global = WEXITSTATUS(status); //return exit status of child;
	else if (WIFSIGNALED(status)) //returns nn-zero if child terminated bc it recieve signal that hasnt been handled
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit: \n", 2);
			g_global = 131;
		}
		else if (WTERMSIG(status) == SIGINT)
		{
			ft_putstr_fd("\n", 2);
			g_global = 130;
		}
	}
}
