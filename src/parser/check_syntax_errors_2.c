/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:35:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/25 00:04:40 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

	
int check_input (t_general *data, t_token *token) // <
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

int check_heredoc (t_general *data, t_token *token) // <<
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

int check_output (t_general *data, t_token *token) // >
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

int check_append (t_general *data, t_token *token) // >>
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