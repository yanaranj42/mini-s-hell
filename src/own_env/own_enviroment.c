/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_enviroment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:54:46 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/29 19:02:46 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
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
	//malloc para la cantidad de elementos de la lista
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
			free_matrix_env(data->env_matrix); // no hace falta proteger que se haga solo si existe, porque la propia funcion lo gestiona
			return (NULL);
		}
		data->env_matrix[i] = ft_strjoin (half_str, tmp->value);
		if (!data->env_matrix[i])
		{
			free (half_str);
			data->env_matrix[i] = NULL;
			free_matrix_env(data->env_matrix);
			return (NULL);
		}
		free (half_str);
		i++;
		tmp = tmp->next;
	}
	data->env_matrix[i] = NULL;
	return (data->env_matrix);
}
/* char	*env_line(char *name, char *value)
{
	char	*line;
	int		i;
	int		j;

	if (!name)
		return (NULL);
	if (!value)
		return (ft_strdup(""));
	line = malloc(sizeof(char *) * ft_strlen(name) + ft_strlen(value) + 2);
	if (!line)
		return (NULL);
	i = -1;
	while (name[++i])
		line[i] = name[i];
	name[i++] = '=';
	j = -1;
	while (value[++j])
		line[i + j] = value[j];
	line[i + j] = '\0';
	return (line);
}

char	**get_matrix_env(t_general *data, t_env *env)
{
	char	**matrix;
	t_env	*tmp;
	int		i;
	(void)data;
	
	if (!env)
		return (NULL);
	matrix = malloc(sizeof(char *) * (env_matrix_base(env) + 1));
	if (!matrix)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
		{
			matrix[i] = env_line(tmp->name, tmp->value);
			if (!matrix[i])
				arr_clean(matrix);
			i++;
		}
		tmp = tmp->next;
	}
	matrix[i] = NULL;
	return (matrix);	
} */
