/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/21 13:23:54 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*void	free_exit(t_general *data) //PARA LIBERAR  EL READLINE ANTES DE HACER EXIT
{
	free(data->read_line);
	exit(data->ret_exit);
}*/
void	free_env(t_env *head)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = head;
	while (tmp)
	{
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
		prev = NULL;
	}
}
/* puede que esta no sea necesaria*/
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
	