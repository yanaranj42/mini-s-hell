/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:21:45 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/25 01:20:25 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	do_eof(t_general *data)
{
	printf(PURPLE "    The night is dark and full of secrets 🌜 ✨\n" END);
	printf("\n");
	free_env(data->env_lst);
	printf("exit\n");
	exit(data->exit_status);
}

void	init_non_bloquing_signals(void)
{
	if (g_signal_received != 0)
		g_signal_received = 0;
	signal(SIGINT, control_c_normal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_heredoc_signals(void)
{
	signal(SIGINT, control_c_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_bloquing_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	init_ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
