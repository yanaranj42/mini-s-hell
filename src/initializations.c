/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 22:03:19 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/29 19:00:13 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data_values(t_general *data, char **env)
{
	data->line = NULL;
	data->first_token = NULL;
	data->pretoken = NULL;
	data->first_token = NULL;
	data->ret_exit = 0;
	data->equal = OK;
	data->env_lst = NULL;
	data->env_matrix = NULL;

	/*	iniciamos el programa haciendo una copia del env y poniendola en
		formato lista y tambien en formato matriz
		ANTES ESTABA EN EL MAIN
	*/
	if (env)
		get_own_env(data, env);
	get_matrix_env(data, data->env_lst);
	/* printf("# Get matrix enviroment:\n\n");
	print_matrix_env(data->env_matrix);
	printf("\n"); */
}

//NO ENTIENDO EL SENTIDO DE CONVERTIR ESTA FUNCION A INT, PORQUE FUERA NO RECIBE NADA, LA DEJO EN VOID


//En pipex metia a saco el enviroment en data->env porque solo podia pasar una variable a ciertas funciones, y en verdad data->env era un puntero al enviroment original. Aqui en cambio construyo mi propio enviroment, que es una copia del original, por eso no lo puedo igualar a saco, sino que tengo que hacer mallocs.

//En proceso de construccion ->     void	init_token_values()

void	init_quote_values(t_general *data)
{
	data->qdata.quotes = 0;
	data->qdata.miniquotes = 0;
}
