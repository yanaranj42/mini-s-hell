/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/16 06:07:54 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "minishell.h"


void	free_env(t_general *data)
{
	int	i;

	i = 0;
	if (data->own_env == NULL)
		return ;
	while (data->own_env[i])
	{
		free(data->own_env[i]);
		i++;
	}
	free(data->own_env);
}


void	free_before_end(t_general *data)
{
	free_env(data);
}

void free_tokens_list(t_general *data)
{
	int i;
	t_token *tmp_token;
	
 	while (data->first_token)
		{
			i = 0;
			tmp_token = data->first_token->next;
			printf ("%p\n", tmp_token);
			printf (" contenido del primer argumento : %s\n", data->first_token->argv[0]);
			while (data->first_token->argv && data->first_token->argv[i]) 
			{
				printf("limpio argv[%d] = %s\n", i, data->first_token->argv[i]);
				free(data->first_token->argv[i]);
				i++;
			}
			printf("me cargo el argv del token\n");
			free(data->first_token->argv);
			printf("mato el token actual\n");
			free(data->first_token);
			data->first_token = tmp_token;
			printf("next token  es = %p\n", data->first_token);
		}
}

// void free_token(t_token *token) // esta funcion solo limpia un nodo de la lista, un token
// {
// 	int i;

// 	i = 0;
// 	while (token->argv[i])
// 	{
// 		free(token->argv[i]);
// 		i++;
// 	}
// 	free(token->argv);
// 	free(token);
// }

//ahora solo tengo un token, pero cuando tenga mas tendre que iterar en un wihile para liberar todos los tokens
