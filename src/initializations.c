/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaja <yaja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 22:03:19 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/04 12:32:27 by yaja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data_values(t_general *data, char **env)
{
	data->line = NULL;
	data->first_token = NULL;
	data->pretoken = NULL;
	data->env_lst = NULL;
	data->ret_exit = 0;
	data->builtin = 0;
	data->paths = NULL;
	data->env_matrix = NULL;
	data->first_cmd = NULL;
	data->exit_status = 0;//same as ret_exit
	data->pipe_fd[0] = -1; //Inicializo a -1 porque no existen fd negativos, asi me aseguro de no machacar ningun otro (y menos los standars, 0, 1 y 2)
	data->pipe_fd[1] = -1; // 
	data->next_cmd_input_fd = -1;

	/*	iniciamos el programa haciendo una copia del env y poniendola en
		formato lista y tambien en formato matriz
		ANTES ESTABA EN EL MAIN
	*/
	if (env)
		get_own_env(data, env);
	get_matrix_env(data, data->env_lst);
}

//NO ENTIENDO EL SENTIDO DE CONVERTIR ESTA FUNCION A INT, PORQUE FUERA NO RECIBE NADA, LA DEJO EN VOID


//En pipex metia a saco el enviroment en data->env porque solo podia pasar una variable a ciertas funciones, y en verdad data->env era un puntero al enviroment original. Aqui en cambio construyo mi propio enviroment, que es una copia del original, por eso no lo puedo igualar a saco, sino que tengo que hacer mallocs.

//En proceso de construccion ->     void	init_token_values()

void	init_quote_values(t_general *data)
{
	data->qdata.quotes = 0;
	data->qdata.miniquotes = 0;
}
