/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudoparser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:53:22 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/27 12:29:34 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


/* void debug_token(t_token *token)
{
	int i;

	i = 0;

	printf ("\n******************* PARSER *******************\n");
	printf("argc = %d\n", token->argc);
	while (token->argv[i])
	{
		printf("argv[%d] = %s\n", i, token->argv[i]);
		i++;
	}
	printf("next apunta a %p\n", token->next);
	printf("back apunta a %p\n", token->back);
} */


void pseudoparser(char *line, t_general *data)
{
	int i;
	int count;
	//primero creo un token
	data->first_token = malloc (sizeof(t_token) * 1); //aqui estoy creando un token, lo que me devuelve el malloc es la direccion de memoria, que la guardo en first token (que antes era null). first token ya esta creado desde el momento que creo data, pero first token no es un token, es solo un puntero que almacenara una direccion de memoria

	i = 0;
	count = 0;
	//luego_lo_relleno;

	data->first_token->argv = ft_split(line, ' '); //el split me crea la matriz, lo que hago es guardar la direccion de memoria de esa matriz en argv
	while (data->first_token->argv[i])
	{
		i++;
		count++;
	}
	data->first_token->argc = count;
	data->first_token->next = NULL;
	data->first_token->back = NULL;
	//debug_token(data->first_token);
}



//no protejo nada porque es un provisional

