/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:21:45 by yanaranj          #+#    #+#             */
/*   Updated: 2024/10/16 11:14:58 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	g_error = 0;

void    norm_sig_handle(int sig)
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
		exit(g_error);//exit status con variable global 
}
//REVISAR
void	norm_sig_heredoc(int sig)
{
		if (sig == SIGINT)
		{
	//		printf("teng que salir\n");
			ft_putendl_fd("", 1);
			rl_replace_line("", 1);
			g_error = 130;
			//me sale por completo del programa
			//return ;
			
		}
}