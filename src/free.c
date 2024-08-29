/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/28 19:07:36 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "minishell.h"


void	free_exit(t_general *data) //PARA LIBERAR  EL READLINE ANTES DE HACER EXIT
{
	free(data->line);
	exit(data->ret_exit);
}
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


void free_tokens_list(t_general *data)
{
	int i;
	t_token *tmp_token;
	
 	while (data->first_token)
		{
			i = 0;
			tmp_token = data->first_token->next;
			printf ("token actual es = %p\n", data->first_token);
			while (data->first_token->argv && data->first_token->argv[i]) 
			{
				printf("limpio argv[%d] = %s\n", i, data->first_token->argv[i]);
				free(data->first_token->argv[i]);
				i++;
			}
			free(data->first_token->argv); //me cargo el argv del token
			free(data->first_token); //mato el token actual
			data->first_token = tmp_token;
			printf("next token es = %p\n\n", data->first_token);
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
