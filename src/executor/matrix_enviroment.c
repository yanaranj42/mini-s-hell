/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_enviroment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:28:49 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/22 17:50:01 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "libft.h"


//BORRAR
void print_matrix_env(char **env_matrix)
{
	int i;

	i = 0;
	while (env_matrix[i])
	{
		printf("    %s\n", env_matrix[i]);
		i++;
	}
}


int env_matrix_base (t_env *env_lst)
{
	int count;
	t_env *tmp;

	count = 0;
	tmp = env_lst;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int		get_matrix_env(t_general *data, t_env *env_lst)
{
	int		i;
	t_env 	*tmp;
	char 	*half_str;

	i = 0;
	tmp = env_lst;
	
	//PENDIENTE COMPROBAR
	//si la lista del env esta vacia, me hago una matriz que la primera posicion sea null (char ** que su posicion 0 es null)

	//De momento dejo que env sea null, como esta por defecto la variable, y miro si el execve se lo come

	
	if (tmp)
	{
		data->env_matrix = malloc (sizeof(char*) * (env_matrix_base(env_lst) + 1));
		if (!data->env_matrix)
		{
			perror_message(NULL, "Failure in matrix enviroment creation");
			return (0);
		}
		while (tmp)
		{
			half_str = ft_strjoin (tmp->name, "=");
			if (!half_str)
			{
				//MENSAJE ERROR
				data->env_matrix[i] = NULL;
				free_matrix_env(data); // no hace falta proteger que se haga solo si existe, porque la propia funcion lo gestiona
				return (0);
			}
			data->env_matrix[i] = ft_strjoin (half_str, tmp->value);
			if (!data->env_matrix[i])
			{
				//MENSAJE ERROR
				free (half_str);
				data->env_matrix[i] = NULL;
				free_matrix_env(data);
				return (0);
			}
			free (half_str);
			i++;
			tmp = tmp->next;
		}
		data->env_matrix[i] = NULL;
		//borrar
		// printf("# Get matrix enviroment:\n\n");
		// print_matrix_env(data->env_matrix);
		// printf("\n");
	}
	return (1);
}




// void	free_matrix_env(t_general *data)
// {
// 	int	i;

// 	i = 0;
// 	if (data->env_matrix == NULL)
// 		return ;
// 	while (data->env_matrix[i])
// 	{
// 		free(data->env_matrix[i]);
// 		i++;
// 	}
// 	free(data->env_matrix);
// }

