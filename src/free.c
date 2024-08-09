/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/08 21:48:49 by mfontser         ###   ########.fr       */
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

void free_token(t_token *token) // esta funcion solo limpia un nodo de la lista, un token
{
	int i;

	i = 0;
	while (token->argv[i])
	{
		free(token->argv[i]);
		i++;
	}
	free(token->argv);
	free(token);
}

void free_tokens_list(t_token *token)
{
	//ahora solo tengo un token, pero cuando tenga mas tendre que iterar en un wihile para liberar todos los tokens
 	free_token(token);
}
	