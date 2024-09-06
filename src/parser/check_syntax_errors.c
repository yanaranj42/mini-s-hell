/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:35:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/03 21:22:02 by mfontser         ###   ########.fr       */
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

int check_pipe (t_general *data, t_token *token)
{
	if (!token->back) // empieza por pipe
		unexpected_token_message("`|'"); //error de salida ($?) 2:command not found
	else if (!token->next) // acaba por pipe
		unexpected_token_message("`|'"); //error de salida 2:command not found
	else if (token->next->type == PIPE) // dos pipes seguidas
		unexpected_token_message("`|'"); //error de salida 2:command not found
	else
		return (1);
	data->exit_status = 2;
	free_tokens_list(data);
	return (0);
}

	
int check_stdin_redirection (t_general *data, t_token *token) // <
{
	if (!token->next) // acaba por <
		unexpected_token_message("`newline'"); //error de salida 2:command not found
	else if (token->next->type == PIPE) // despues de < viene una pipe
		unexpected_token_message("`|'"); //error de salida 2:command not found
	else if (token->next->type == STDIN_REDIRECTION) // despues de < viene un <
		unexpected_token_message("`<'"); //error de salida 2:command not found
	else
		return (1);
	data->exit_status = 2;
	free_tokens_list(data);
	return (0);
}

int check_stdin_double_redirection (t_general *data, t_token *token) // <<
{
	if (!token->next) // acaba por <<
		unexpected_token_message("`newline'"); //error de salida 2:command not found
	else if (token->next->type == PIPE) // despues de << viene una pipe
		unexpected_token_message("`|'"); //error de salida 2:command not found
	else if (token->next->type == STDIN_REDIRECTION) // despues de << viene un <
		unexpected_token_message("`<'"); //error de salida 2:command not found
	else if (token->next->type == STDIN_DOUBLE_REDIRECTION) // despues de << viene un <<
		unexpected_token_message("`<<'"); //error de salida 2:command not found
	else if (token->next->type == STDOUT_REDIRECTION) // despues de << viene un >
		unexpected_token_message("`>'"); //error de salida 2:command not found
	else if (token->next->type == STDOUT_DOUBLE_REDIRECTION) // despues de << viene un >>
		unexpected_token_message("`>>'"); //error de salida 2:command not found
	else
		return (1);
	data->exit_status = 2;
	free_tokens_list(data);
	return (0);
}

int check_stdout_redirection (t_general *data, t_token *token) // >
{
	if (!token->next) // acaba por >
		unexpected_token_message("`newline'"); //error de salida 2:command not found
	else if (token->next->type == PIPE) // despues de > viene una pipe
		unexpected_token_message("`|'"); //error de salida 2:command not found
	else if (token->next->type == STDIN_REDIRECTION) // despues de > viene un <
		unexpected_token_message("`<'"); //error de salida 2:command not found
	else if (token->next->type == STDOUT_REDIRECTION) // despues de > viene un >
		unexpected_token_message("`>'"); //error de salida 2:command not found
	else
		return (1);
	data->exit_status = 2;
	free_tokens_list(data);
	return (0);
}

int check_stdout_double_redirection (t_general *data, t_token *token) // >>
{
	if (!token->next) // acaba por >>
		unexpected_token_message("`newline'"); //error de salida 2:command not found
	else if (token->next->type == PIPE) // despues de >> viene una pipe
		unexpected_token_message("`|'"); //error de salida 2:command not found
	else if (token->next->type == STDOUT_REDIRECTION) // despues de >> viene un >
		unexpected_token_message("`>'"); //error de salida 2:command not found
	else if (token->next->type == STDOUT_DOUBLE_REDIRECTION) // despues de >> viene un >>
		unexpected_token_message("`>>'"); //error de salida 2:command not found
	else if (token->next->type == STDIN_REDIRECTION) // despues de >> viene un <
		unexpected_token_message("`<'"); //error de salida 2:command not found
	else if (token->next->type == STDIN_DOUBLE_REDIRECTION) // despues de >> viene un <<
		unexpected_token_message("`<<'"); //error de salida 2:command not found
	else
		return (1);
	data->exit_status = 2;
	free_tokens_list(data);
	return (0);
}

int check_syntax_errors (t_general *data)
{
	t_token *tmp1_token;

	tmp1_token = data->first_token;
	while (tmp1_token)
	{
		if (tmp1_token->type == PIPE)
		{
			if (check_pipe (data, tmp1_token) == 0)
				return (0);
		}
		if (tmp1_token->type == STDIN_REDIRECTION)
		{
			if (check_stdin_redirection (data, tmp1_token) == 0)
				return (0);
		}
		if (tmp1_token->type == STDIN_DOUBLE_REDIRECTION)
		{
			if (check_stdin_double_redirection (data, tmp1_token) == 0)
				return (0);
		}
		if (tmp1_token->type == STDOUT_REDIRECTION)
		{
			if (check_stdout_redirection (data, tmp1_token) == 0)
				return (0);
		}
		if (tmp1_token->type == STDOUT_DOUBLE_REDIRECTION)
		{
			if (check_stdout_double_redirection (data, tmp1_token) == 0)
				return (0);
		}
		tmp1_token = tmp1_token->next;
	}
	return (1);
}