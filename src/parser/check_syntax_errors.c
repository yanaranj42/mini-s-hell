/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaja <yaja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:35:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/04 12:42:57 by yaja             ###   ########.fr       */
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

	
int check_INPUT (t_general *data, t_token *token) // <
{
	if (!token->next) // acaba por <
		unexpected_token_message("`newline'"); //error de salida 2:command not found
	else if (token->next->type == PIPE) // despues de < viene una pipe
		unexpected_token_message("`|'"); //error de salida 2:command not found
	else if (token->next->type == INPUT) // despues de < viene un <
		unexpected_token_message("`<'"); //error de salida 2:command not found
	else
		return (1);
	data->exit_status = 2;
	free_tokens_list(data);
	return (0);
}

int check_HEREDOC (t_general *data, t_token *token) // <<
{
	if (!token->next) // acaba por <<
		unexpected_token_message("`newline'"); //error de salida 2:command not found
	else if (token->next->type == PIPE) // despues de << viene una pipe
		unexpected_token_message("`|'"); //error de salida 2:command not found
	else if (token->next->type == INPUT) // despues de << viene un <
		unexpected_token_message("`<'"); //error de salida 2:command not found
	else if (token->next->type == HEREDOC) // despues de << viene un <<
		unexpected_token_message("`<<'"); //error de salida 2:command not found
	else if (token->next->type == OUTPUT) // despues de << viene un >
		unexpected_token_message("`>'"); //error de salida 2:command not found
	else if (token->next->type == APPEND) // despues de << viene un >>
		unexpected_token_message("`>>'"); //error de salida 2:command not found
	else
		return (1);
	data->exit_status = 2;
	free_tokens_list(data);
	return (0);
}

int check_OUTPUT (t_general *data, t_token *token) // >
{
	if (!token->next) // acaba por >
		unexpected_token_message("`newline'"); //error de salida 2:command not found
	else if (token->next->type == PIPE) // despues de > viene una pipe
		unexpected_token_message("`|'"); //error de salida 2:command not found
	else if (token->next->type == INPUT) // despues de > viene un <
		unexpected_token_message("`<'"); //error de salida 2:command not found
	else if (token->next->type == OUTPUT) // despues de > viene un >
		unexpected_token_message("`>'"); //error de salida 2:command not found
	else
		return (1);
	data->exit_status = 2;
	free_tokens_list(data);
	return (0);
}

int check_APPEND (t_general *data, t_token *token) // >>
{
	if (!token->next) // acaba por >>
		unexpected_token_message("`newline'"); //error de salida 2:command not found
	else if (token->next->type == PIPE) // despues de >> viene una pipe
		unexpected_token_message("`|'"); //error de salida 2:command not found
	else if (token->next->type == OUTPUT) // despues de >> viene un >
		unexpected_token_message("`>'"); //error de salida 2:command not found
	else if (token->next->type == APPEND) // despues de >> viene un >>
		unexpected_token_message("`>>'"); //error de salida 2:command not found
	else if (token->next->type == INPUT) // despues de >> viene un <
		unexpected_token_message("`<'"); //error de salida 2:command not found
	else if (token->next->type == HEREDOC) // despues de >> viene un <<
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
		if (tmp1_token->type == INPUT)
		{
			if (check_INPUT (data, tmp1_token) == 0)
				return (0);
		}
		if (tmp1_token->type == HEREDOC)
		{
			if (check_HEREDOC (data, tmp1_token) == 0)
				return (0);
		}
		if (tmp1_token->type == OUTPUT)
		{
			if (check_OUTPUT (data, tmp1_token) == 0)
				return (0);
		}
		if (tmp1_token->type == APPEND)
		{
			if (check_APPEND (data, tmp1_token) == 0)
				return (0);
		}
		tmp1_token = tmp1_token->next;
	}
	return (1);
}