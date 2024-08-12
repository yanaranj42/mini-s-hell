/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/12 12:46:23 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "minishell.h"

/* he tenido que poner esta funcion porque debe borrar los nodos con
el void, no podia hacerlo directamente con el free. No se si hay alguna
similar en el bonus del libft, porque estaria bien usarla. */

static void *ft_memdel(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	free_env(t_env *head)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = head;
	while (tmp)
	{
		if (tmp->name)
			tmp->name = ft_memdel(tmp->name);
		if (tmp->value)
			tmp->value = ft_memdel(tmp->value);
		prev = tmp;
		tmp = tmp->next;
		ft_memdel(prev);
		prev = NULL;
	}
}

void	free_before_end(t_general *data)
{
	free_env(data->env_lst);
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
	