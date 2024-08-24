/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:35:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/24 21:53:33 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int check_pipe (t_general *data, t_token *token)
{
	
	if (!token->back) //empieza por pipe
	{
		free_tokens_list(data);
		printf("Drackyshell: syntax error near unexpected token `|'\n"); //modificar con lo de perror y error de salida 2:command not found
		return (0);
	}
	else if (!token->next) // acaba por pipe
	{
		free_tokens_list(data);
		printf("Drackyshell: syntax error near unexpected token `|'\n"); //modificar con lo de perror y error de salida 2:command not found
		return (0);
	}
	else if (token->next->type == PIPE)
	{
		free_tokens_list(data);
		printf("Drackyshell: syntax error near unexpected token `|'\n"); //modificar con lo de perror y error de salida 2:command not found
		return (0);
	}

	return (1);

	//si hay "echo hola |> outfile" crea el outfile, pero no mete dentro el hola, pero eso ya seran maneras de ejecutar
		//lo mismo si es |>>
	//si hay "echo hola |< outfile"  creo que no hace nada. Da error si el outfile no existe
		//si es |<< se queda con el proceso abierto
}
	
int check_stdin_redirection (t_general *data, t_token *token) // <
{
	if (!token->back) 
	{
		free_tokens_list(data);
		printf("Drackyshell: syntax error near unexpected token `newline'\n"); //modificar con lo de perror y error de salida 2:command not found
		return (0);
	}
	return (1);
}

// else if (tmp2 && tmp1_token == data->first_token && (tmp1_token->argv[0] == "<" || tmp1_token->argv[0] == "<<" || tmp1_token->argv[0] == ">>")  && tmp2_token->argv[0] == "|") 
		// {
		// 	free_tokens_list(data);
		// 	printf("Drackyshell: syntax error near unexpected token `|'\n"); //modificar con lo de perror y error de salida 2:command not found
		// 	return (0);
		// }
		// else if (tmp2 && tmp1_token == data->first_token && tmp1_token->argv[0] == ">" && tmp2_token->argv[0] == "|") 
		// {
		// 	free_tokens_list(data);
		// 	printf("Drackyshell: syntax error near unexpected token `newline'\n"); //modificar con lo de perror y error de salida 2:command not found
		// 	return (0);
		// }

int check_stdin_double_redirection (t_general *data, t_token *token) // <<
{
	if (!token->back) 
	{
		free_tokens_list(data);
		printf("Drackyshell: syntax error near unexpected token `newline'\n"); //modificar con lo de perror y error de salida 2:command not found
		return (0);
	}
	return (1);
}

int check_stout_redirection (t_general *data, t_token *token) // >
{
	if (!token->back) 
	{
		free_tokens_list(data);
		printf("Drackyshell: syntax error near unexpected token `newline'\n"); //modificar con lo de perror y error de salida 2:command not found
		return (0);
	}
	return (1);
}

int check_stout_double_redirection (t_general *data, t_token *token) // >>
{
	if (!token->back) 
	{
		free_tokens_list(data);
		printf("Drackyshell: syntax error near unexpected token `newline'\n"); //modificar con lo de perror y error de salida 2:command not found
		return (0);
	}
	return (1);
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
			if (check_stout_redirection (data, tmp1_token) == 0)
				return (0);
		}
		if (tmp1_token->type == STDOUT_DOUBLE_REDIRECTION)
		{
			if (check_stout_double_redirection (data, tmp1_token) == 0)
				return (0);
		}
		tmp1_token = tmp1_token->next;
	}

	return (1);
}