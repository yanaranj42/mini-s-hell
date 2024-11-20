/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 22:03:19 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 16:18:25 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data_values(t_general *data, char **env)
{
	data->line = NULL;
	data->first_token = NULL;
	data->pretoken = NULL;
	data->env_lst = NULL;
	data->first_token = NULL;
	data->first_xtkn = NULL;
	data->paths = NULL;
	data->env_matrix = NULL;
	data->first_cmd = NULL;
	data->exit_status = 0;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->next_cmd_input_fd = -1;
	data->equal = 1;
	(void)env;
}

void	init_quote_values(t_general *data)
{
	data->qdata.quotes = 0;
	data->qdata.miniquotes = 0;
}

void	init_fd_values(t_general *data)
{
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->next_cmd_input_fd = -1;
}

/* void	init_signal()
{
	signal(SIGINT, norm_sig_handle);
	signal(SIGQUIT, SIG_IGN);
} */
