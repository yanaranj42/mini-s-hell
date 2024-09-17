/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/17 15:41:47 by yanaranj         ###   ########.fr       */
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

/*YAJA:
* hay que rehacer el arr_clean, porque seguro lo usamos en otras partes y no tenemos la funcion de memdel
* quiero mirar como hacer directamente con el free (un swap quiza? esta por verse) 
*/
void	*ft_memdel(void *ptr)
{
	if (ptr)
		free(ptr);
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