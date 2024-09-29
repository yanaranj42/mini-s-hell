/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/29 18:51:49 by yanaranj         ###   ########.fr       */
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
			while (data->first_token->argv && data->first_token->argv[i]) 
			{
				free(data->first_token->argv[i]);
				i++;
			}
			free(data->first_token->argv);
			free(data->first_token);
			data->first_token = tmp_token;
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

/*YAJA:
* hay que rehacer el arr_clean, porque seguro lo usamos en otras partes y no tenemos la funcion de memdel
* quiero mirar como hacer directamente con el free (un swap quiza? esta por verse) 
*/
void	*ft_memdel(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (NULL);
}

char	**arr_clean(char **arr)
{
	int		i;

	
	i=0;
	if (!arr)
		return (NULL);
	while (arr && arr[i] != NULL)
	{
		arr[i] = ft_memdel(arr[i]);
		i++;
	}
	arr = ft_memdel(arr);
	return (NULL);
}

void	free_matrix_env(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL; // libero la matriz y la vuelvo a poner a null, para proteger que si en otra parte del codigo la intento liberar cuando ya estaba liberada, que no me de un double free (si hago free de null no pasa nada). O si en otra parte del codigo quiero usar el enviroment, ver que no hay, que es null.
	//Cuando libero, libero la memoria, pero el puntero sigue apuntando a ese espacio. Al ponerlo a NULL lo que hago es que el puntero ya no apunte a ninguna parte.
}