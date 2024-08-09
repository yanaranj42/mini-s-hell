/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/09 14:14:05 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "minishell.h"


void	free_env(t_general *data)
{
	int	i;

	i = 0;
	if (data->env_lst == NULL)
		return ;
	while (data->env_lst[i])
	{
		free(data->env_lst[i]);
		i++;
	}
	free(data->env_lst);
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
	