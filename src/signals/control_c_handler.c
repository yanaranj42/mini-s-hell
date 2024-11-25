/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_c_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:48:15 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/25 01:20:49 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	control_c_heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		write(2, "\n", 1);
		exit(130);
	}
}

void	control_c_normal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_signal_received = 1;
	}
}
