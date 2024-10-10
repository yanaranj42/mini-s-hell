/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 22:03:19 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/10 01:56:01 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data_values(t_general *data)
{
	data->line = NULL;
	data->first_token = NULL;
	data->pretoken = NULL;
	data->env_lst = NULL;
	data->first_token = NULL;
	data->paths = NULL;
	data->env_matrix = NULL;
	data->first_cmd = NULL;
	data->exit_status = 0;
	data->pipe_fd[0] = -1; //Inicializo a -1 porque no existen fd negativos, asi me aseguro de no machacar ningun otro (y menos los standars, 0, 1 y 2)
	data->pipe_fd[1] = -1; // 
	data->next_cmd_input_fd = -1;

}


//En pipex metia a saco el enviroment en data->env porque solo podia pasar una 
//variable a ciertas funciones, y en verdad data->env era un puntero al 
//enviroment original. Aqui en cambio construyo mi propio enviroment, que es 
//una copia del original, por eso no lo puedo igualar a saco, sino que tengo 
//que hacer mallocs.

//En proceso de construccion ->     void	init_token_values()

void	init_quote_values(t_general *data)
{

	data->qdata.quotes = 0;
	data->qdata.miniquotes = 0;
}

void    init_signal(t_general *data)
{
	(void)data;
    signal(SIGINT, norm_sig_handle);
    signal(SIGQUIT, SIG_IGN);
}
