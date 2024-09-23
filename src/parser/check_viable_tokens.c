/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_viable_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:35:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/27 13:33:37 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//mirar si tengo dos pipes seguidas etc..

/*CAMBIAR LOS PRINTS POR PERROR_MSG*/
int check_pipe (t_general *data)
{
	t_token *tmp1_token;
	t_token *tmp2_token;

	tmp1_token = data->first_token;
	if (data->first_token)
		tmp2_token = data->first_token->next;
	else
		tmp2_token = NULL;
	while (tmp1_token && tmp_token->next)
	{
		if (tmp1_token->argv[0] == "|" && tmp1_token == data->first_token) 
		{
			free_tokens_list(data);
			perror_message("Drackyshell", ERROR3);
			//printf("Drackyshell: syntax error near unexpected token `|'\n"); //modificar con lo de perror y error de salida 2:command not found
			return (0);
		}
		else if (tmp2 && tmp1_token->argv[0] == "|" && tmp2_token->argv[0] == "|")
		{
			free_tokens_list(data);
			printf("Drackyshell: syntax error near unexpected token `|'\n"); //modificar con lo de perror y error de salida 2:command not found
			return (0);
		}
		tmp1_token = tmp1_token->next;
		tmp2_token = tmp2_token->next;
	}
	return (1);
}

int check_separator_combinations (t_general *data)
{
	t_token *tmp1_token;
	t_token *tmp2_token;

	tmp1_token = data->first_token;
	if (data->first_token)
		tmp2_token = data->first_token->next;
	else
		tmp2_token = NULL;
	while (tmp1_token && tmp_token->next)
	{
		if (tmp2 && tmp1_token == data->first_token && tmp1_token->argv[0] == "|" && (tmp2_token->argv[0] == "<") || tmp2_token->argv[0] == "<<") 
		{
			free_tokens_list(data);
			printf("Drackyshell: syntax error near unexpected token `|'\n"); //modificar con lo de perror y error de salida 2:command not found
			return (0); 
		}
		else if (tmp2 && tmp1_token == data->first_token && tmp1_token->argv[0] == "|" && (tmp2_token->argv[0] == ">") || tmp2_token->argv[0] == ">>") 
		{
			free_tokens_list(data);
			printf("Drackyshell: syntax error near unexpected token `|'\n"); //modificar con lo de perror y error de salida 2:command not found
			return (0);
		}
		else if (tmp2 && tmp1_token == data->first_token && (tmp1_token->argv[0] == "<" || tmp1_token->argv[0] == "<<" || tmp1_token->argv[0] == ">>")  && tmp2_token->argv[0] == "|") 
		{
			free_tokens_list(data);
			printf("Drackyshell: syntax error near unexpected token `|'\n"); //modificar con lo de perror y error de salida 2:command not found
			return (0);
		}
		else if (tmp2 && tmp1_token == data->first_token && tmp1_token->argv[0] == ">" && tmp2_token->argv[0] == "|") 
		{
			free_tokens_list(data);
			printf("Drackyshell: syntax error near unexpected token `newline'\n"); //modificar con lo de perror y error de salida 2:command not found
			return (0);
		}
		
		tmp1_token = tmp1_token->next;
		tmp2_token = tmp2_token->next;
	}
}

int viable_separators (t_general *data)
{
	t_token *tmp1_token;
	t_token *tmp2_token;


	tmp1_token = data->first_token;
	if (data->first_token)
		tmp2_token = data->first_token->next;
	// redireccion derecha

	// redireccion izqierda

	// pipe
		//si hay una doble pipe actuaria como un or, por lo que intentara hacer el primer comando y si puede ya no hara el segundo. Si no puede ejecutara el segundo y listo. Yo lo interpreto como dos pipes separadas, porque no hago bonus
	if (check_pipe (data) == 0)
		return (0);

	//combinaciones
	if (check_separator_combinations (data) == 0)
		return (0);

}



int check_viable_tokens (t_general *data)
{
	if (viable_separators (data) == 0)
		return (0);



	return (1);
}