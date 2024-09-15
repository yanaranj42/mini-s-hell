/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 22:03:19 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/15 20:30:41 by mfontser         ###   ########.fr       */
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
	data->ret_exit = 0;
	data->paths = NULL;
	data->env_matrix = NULL;
	data->first_cmd = NULL;
	data->exit_status = 0;
	data->pipe_fd[0] = 0;
	data->next_cmd_input_fd = 0;

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
