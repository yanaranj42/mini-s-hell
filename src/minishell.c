/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:00:25 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/17 15:33:47 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	minishell_loop(t_general *data)
{
	data->line = readline("🔥 ÐrackyŠhell ▶ ");
	if (!data->line)
	{
		printf(PURPLE"    The night is dark and full of secrets 🌜 ✨\n\n"END);
		do_eof(data);
	}
	if (g_error != 0)
		data->exit_status = g_error; // SI HAGO CONTROL C, LO QUE HACE ES PARAR EL READLINE, HACER EL CONTROL C, Y LUEGO SIGUE ESTANDO ACTIVO EL MISMO READLINE, NO ES QUE EMPIECE UNO NUEVO. POR ESO, PARA PODER ACTUALIZAR EL EXIT STATUS CON ESE VALOR, TENGO QUE HACERLO DESPUES DE EL READLINE, PORQUE SINO CUANDO HAGA ECHO $? NO EXPANDIRA EL VALOR QUE TOCA A TIEMPO. SI LO HAGO DESPUES DEL EXECUTOR O ANTES DEL READLINE, SE ESTARIA ACTUALIZANDO PARA LA PROXIMA VUELTA, OSEA PARA EL PROXIMO COMANDO, OSEA TARDE.
	add_history(data->line);
	if (lexer(data) == 0)
	{
		free(data->line);
		return (0);
	}
	if (parser(data) == 0 || check_syntax_errors(data) == 0)
	{
		free(data->line);
		return (0);
	}
	if (expansor(data) == 0)
	{
		free(data->line);
		return (0);
	}
	if (executor(data) == 0)
	{
		free(data->line);
		return (0);
	}
	free_before_next_round(data);

	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_general	data;

	(void)argv;
	if (argc != 1)
	{
		too_many_parameters();
		return (1);
	}
	init_data_values(&data, env);
	init_signal();
	if (get_own_env(&data, env) == 0)
		return (1);
	while (1)
	{
		if (minishell_loop (&data) == 0)
			continue ;
	}
	free_env(data.env_lst);
	return (0);
}
