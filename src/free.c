/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/04 20:47:00 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "minishell.h"


void	free_exit(t_general *data) //PARA LIBERAR  EL READLINE ANTES DE HACER EXIT (BUILTIN)
{
	free(data->line);
	exit(data->ret_exit);
}

void	free_data_paths (char **paths)
{
	int i;

	i = 0;
	if (paths == NULL)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
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


void	free_matrix_env(t_general *data)
{
	int	i;

	i = 0;
	if (data->env_matrix == NULL)
		return ;
	while (data->env_matrix[i])
	{
		free(data->env_matrix[i]);
		i++;
	}
	free(data->env_matrix);
	data->env_matrix = NULL; // libero la matriz y la vuelvo a poner a null, para proteger que si en otra parte del codigo la intento liberar cuando ya estaba liberada, que no me de un double free (si hago free de null no pasa nada). O si en otra parte del codigo quiero usar el enviroment, ver que no hay, que es null.
	//Cuando libero, libero la memoria, pero el puntero sigue apuntando a ese espacio. Al ponerlo a NULL lo que hago es que el puntero ya no apunte a ninguna parte.
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
