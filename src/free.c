/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/15 15:45:32 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "minishell.h"


//YAJA:
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

void	unset_free(t_env *env)
{
	ft_memdel(env->name);
	ft_memdel(env->value);
	ft_memdel(env);
}


void	free_exit(t_general *data) //PARA LIBERAR  EL READLINE ANTES DE HACER EXIT (BUILTIN)
{
	free(data->line);
	exit(data->exit_status);
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
	t_token *tmp_token;
	
 	while (data->first_token)
	{
		tmp_token = data->first_token->next;
		// printf ("token actual es = %p\n", data->first_token);
		// while (data->first_token->argv && data->first_token->argv[i]) 
		// {
		// 	printf("limpio argv[%d] = %s\n", i, data->first_token->argv[i]);
		// 	free(data->first_token->argv[i]);
		// 	i++;
		// }
		// free(data->first_token->argv); //me cargo el argv del token
		printf("limpio el contenido del token = %s\n", data->first_token->content);
		free(data->first_token->content); //SI?????????????????????//me cargo el contenido del token
		free(data->first_token); //mato el token actual
		data->first_token = NULL;
		data->first_token = tmp_token;
		printf("next token es = %p\n\n", data->first_token);
	}
}

/*void free_xtkns_list(t_general *data)
{
	t_xtkn *tmp_xtkn;
 	while (data->first_xtkn)
	{
		tmp_xtkn = data->first_xtkn->next;
		printf("limpio el contenido del xtoken = %s\n", data->first_xtkn->content);
		free(data->first_xtkn->content); //SI?????????????????????//me cargo el contenido del token
		free(data->first_xtkn); //mato el xtoken actual
		data->first_xtkn = NULL;
		data->first_xtkn = tmp_xtkn;
		printf("next token es = %p\n\n", data->first_xtkn);
	}
}*/


void 	free_pretoken_argv (char **argv)
{
	int i;
	i = 0;
		while (argv && argv[i]) // SI??????????
		{
			free(argv[i]);
			i++;
		}
		free(argv); // SI??????????
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


void free_cmd(t_general *data)
{
	int i;
	t_cmd 		*tmp_cmd;
	t_redir 	*tmp_redir;
	
 	while (data->first_cmd)
	{
		i = 0;
		tmp_cmd = data->first_cmd->next;
		printf ("cmd actual es = %p\n", data->first_cmd);
		while (data->first_cmd->argv && data->first_cmd->argv[i]) 
		{
			printf("limpio argv[%d] = %s\n", i, data->first_cmd->argv[i]);
			free(data->first_cmd->argv[i]);
			i++;
		}
		free(data->first_cmd->argv); //me cargo el argv del cmd
		data->first_cmd->argv = NULL;
		// printf("limpio el path = %s\n", data->first_cmd->path);
		// free(data->first_cmd->path); No tengo que liberar path porque no lo tengo,lo obtengo en el hijo y el padre no lo tiene, por lo que si intento liberarlo me da segfault. En el hijo se autolibera porque sale haciendo exit
		printf("limpio las redirecciones\n");
		while (data->first_cmd->first_redir)
		{
			printf ("archivo de redireccion: %s\n", data->first_cmd->first_redir->file_name);
			tmp_redir = data->first_cmd->first_redir->next;
			free (data->first_cmd->first_redir->file_name);
			free (data->first_cmd->first_redir);
			data->first_cmd->first_redir = tmp_redir;
		}
		free (data->first_cmd->first_redir);
		data->first_cmd->first_redir = NULL;
		free(data->first_cmd); //mato el cmd actual
		data->first_cmd = tmp_cmd;
		printf("next token es = %p\n\n", data->first_token);
	}
	data->first_cmd = NULL;
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
