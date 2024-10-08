/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 22:03:19 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/08 16:42:24 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data_values(t_general *data, char **env)
{
	//YAJA: 
	data->env_lst = NULL;
	data->ret_exit = 0;
	data->builtin = 0;
	
	data->line = NULL;
	data->first_token = NULL;
	data->pretoken = NULL;
	data->paths = NULL;
	data->env_matrix = NULL;
	data->first_cmd = NULL;
	data->exit_status = 0;//same as ret_exit
	data->pipe_fd[0] = -1; //Inicializo a -1 porque no existen fd negativos, asi me aseguro de no machacar ningun otro (y menos los standars, 0, 1 y 2)
	data->pipe_fd[1] = -1; // 
	data->next_cmd_input_fd = -1;

	if (env)
		get_own_env(data, env);
	/* else //al llamar env ha de pillar esta lista
		basic_env(data); */
	get_matrix_env(data, data->env_lst);
}


//En pipex metia a saco el enviroment en data->env porque solo podia pasar una variable a ciertas funciones, y en verdad data->env era un puntero al enviroment original. Aqui en cambio construyo mi propio enviroment, que es una copia del original, por eso no lo puedo igualar a saco, sino que tengo que hacer mallocs.

//En proceso de construccion ->     void	init_token_values()

void	init_quote_values(t_general *data)
{
	data->qdata.quotes = 0;
	data->qdata.miniquotes = 0;
}

void	init_signals(t_general *data, int code, int init)
{
	/*	si init = 0 -> es el inicio del programa
		si init = 1 --> se cambias las signals para heredoc.
		sig_int(int code) SIGINT --> signal del CTRL + C
		sig_quit(int code) SIGQUIT --> signal del CTRL + \
		utilizamos el data para el exit status
	*/
	(void)data;
	if (init == 0)
	{
		if (code == SIGINT)
			sig_init();
		if (code ==  SIGQUIT)
			sig_quit();
	}
	/* else if (init == 1)
	{
		if (code == SIGINT)
			heredoc_sig(code);
		if (code == SIGQUIT)
		
	} */
	
}

