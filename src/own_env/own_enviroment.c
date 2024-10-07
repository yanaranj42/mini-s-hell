/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_enviroment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:54:46 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/07 13:42:40 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//si no tenemos ENV, debemos agregar PWD, SHLVL, _=/usr/... y OLDPWD cuando corresponda
//y podemos crear un env a base de hacer exports
//void	basic_env(t_general *data)

//agrega la variable a la lista
void	env_to_lst(t_general *data, t_env *my_env)
{
	t_env	*head;
	t_env	*tmp;
	
	head = data->env_lst;
	tmp = head;
	if (my_env == NULL)
		return ;
	if (head == NULL)
	{ 
		data->env_lst = my_env;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = my_env;
}

int	get_own_env(t_general *data, char **env)
{
	t_env	*s_env;
	int		i;

	i = -1;
	while (env[++i])
	{
		s_env = malloc(sizeof(t_env));
		if (!s_env)
			return (perror_message(NULL, ERR02), 0);
		s_env->name = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		s_env->value = ft_strdup(getenv(s_env->name));
		s_env->next = NULL;
		env_to_lst(data, s_env);
		if (!s_env->name || !s_env->value)
			return (free_env(data->env_lst), 0);
			//FALTARIA EL MENSAJE DE ERROR, NO?
	}
	return (1);
}
//ENV EN FORMA DE MATRIZ
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
/*cuenta todas las variables aunque estas no tengan valor*/
int env_matrix_base (t_env *env)
{
	int count;
	t_env *tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (++count);
}

char	**get_matrix_env(t_general *data, t_env *env_lst)
{
	t_env 	*tmp;
	char 	*half_str;
	int		i;

	if (!env_lst)
		return (NULL);
	data->env_matrix = malloc(sizeof(char*) * (env_matrix_base(env_lst) + 1));
	if (!data->env_matrix)
		return (perror_message(NULL, "Failure in matrix enviroment creation"), NULL);
	i = 0;
	tmp = env_lst;
	while (tmp)
	{
		half_str = ft_strjoin (tmp->name, "=");
		if (!half_str)
		{
			data->env_matrix[i] = NULL;
			arr_clean(data->env_matrix); // no hace falta proteger que se haga solo si existe, porque la propia funcion lo gestiona
			return (NULL);
		}
		data->env_matrix[i] = ft_strjoin (half_str, tmp->value);
		if (!data->env_matrix[i])
		{
			free (half_str);
			data->env_matrix[i] = NULL;
			arr_clean(data->env_matrix);
			return (NULL);
		}
		free (half_str);
		i++;
		tmp = tmp->next;
	}
	data->env_matrix[i] = NULL;
	return (data->env_matrix);
}
