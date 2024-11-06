/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_syntax_errors_checking.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:35:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/06 04:24:27 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


//Para los perror podria definir en el .h lo stipos de syntax error, tipo, diferentes unexpectet tokens:
// SPACE = 0
// PIPE = 1
// ...
// Entoces generar una funcion void syntax_error (int i), y segun el int que le llega printa un error u otro, para agrupar. 
// Sino lo dejamos tal cual dentro de las funciones aqui, ya que es una linea y no cambia nada a nivel de espacio.

void check_number_of_heredocs (t_general *data)
{
	t_token *tmp_token;
	int count;

	tmp_token = data->first_token;
	count = 0;
	while (tmp_token)
	{
		if (tmp_token->type == HEREDOC)
			count++;
		tmp_token = tmp_token->next;
	}
	if (count > 16)
	{
		free (data->line);
		free_tokens_list(data);
		maximum_heredoc_exceeded ();
		exit (1);
	}
}

int check_syntax_errors_2 (t_general *data, t_token *tmp_token)
{

	if (tmp_token->type == HEREDOC)
	{
		if (check_heredoc (data, tmp_token) == 0)
			return (0);
	}
	else if (tmp_token->type == OUTPUT)
	{
		if (check_output (data, tmp_token) == 0)
			return (0);
	}
	else if (tmp_token->type == APPEND)
	{
		if (check_append (data, tmp_token) == 0)
			return (0);
	}
	return (1);
}

int check_syntax_errors (t_general *data)
{
	t_token *tmp_token;

	tmp_token = data->first_token;
	while (tmp_token)
	{
		if (tmp_token->type == PIPE)
		{
			if (check_pipe (data, tmp_token) == 0)
				return (0);
		}
		else if (tmp_token->type == INPUT)
		{
			if (check_input (data, tmp_token) == 0)
				return (0);
		}
		else 
		{
			if (check_syntax_errors_2 (data, tmp_token) == 0)
				return (0);
		}
		tmp_token = tmp_token->next;
	}
	check_number_of_heredocs (data);
	return (1);
}