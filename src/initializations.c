/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 22:03:19 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/27 12:11:44 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_data_values(t_general *data, char **env)
{
	data->line = NULL;
	data->first_token = NULL;
	data->pretoken = NULL;
	data->own_env = NULL;
	data->env_lst = NULL;
	data->first_token = NULL;
	data->ret_exit = 0;
	if (env)
		get_own_env(data, env);
	return (0);
}

//En pipex metia a saco el enviroment en data->env porque solo podia pasar una variable a ciertas funciones, y en verdad data->env era un puntero al enviroment original. Aqui en cambio construyo mi propio enviroment, que es una copia del original, por eso no lo puedo igualar a saco, sino que tengo que hacer mallocs.

//En proceso de construccion ->     void	init_token_values()

void	init_quote_values(t_general *data)
{
	data->qdata.quotes = 0;
	data->qdata.miniquotes = 0;
}
