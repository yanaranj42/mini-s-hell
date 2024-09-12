/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaja <yaja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:44:50 by yaja              #+#    #+#             */
/*   Updated: 2024/09/12 13:40:12 by yaja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
//MOVER AL UNSET
void	unset_free(t_env *env)
{
	ft_memdel(env->name);
	ft_memdel(env->value);
	ft_memdel(env);
}

char	*find_env_var(t_general *data, char *var_name)
{
    t_env	*env;
    int		len_env_name;
    int		len_var_name;
	
	int i = -1;//BORRAR

	if (!var_name)
		return (NULL);
	env = data->env_lst;
	len_var_name = ft_strlen(var_name);
	while (env != NULL)
	{
		i++;
		len_env_name = ft_strlen(env->name);
		if (ft_strncmp(env->name, var_name, len_env_name) == 0 \
			&& (len_env_name == len_var_name))
		{
			printf("match found on variable: %i %s\n", i, env->name);
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

int	env_add_last(t_general *data, char *name, char *value, int val)
{
	t_env	*new_env;
	
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (KO);
	new_env->name = ft_strdup(name);	
	new_env->value = ft_strdup(value);
	new_env->next = NULL;
	if (!new_env->name || (val && !new_env->value))
	{
		unset_free(new_env);
		return (1);
	}
	env_to_lst(data, new_env);
	return (0);
}

int	add_upd_env(t_general *data, char *name, char *value)
{
	t_env	*env;
	int		val;

	val = 1;
	if (value == NULL)
		value = ft_strdup("");
		//val = 0;
	env = data->env_lst;
	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0 \
			&& (ft_strlen(env->name) == ft_strlen(name)))//si en name coincide con uno de la lista y sus lens tambien
		{
			printf(GREEN"HAY match en la lista\t"END);
			printf(RED"Procedemos a borrar el valor: %s\n"END, env->value);
			if (env->value)
				free(env->value);//borramos el valor que tiene en la lista
			env->value = ft_strdup(value);//ponemos el nuevo valor en esa posicion
			printf(GREEN"el nuevo valor es: %s\n"END, env->value);
			/* if (!env->value && value)
				printf("SALIMOS CON ERROR\n");
				return (error_brk(data, "malloc", NULL, 12)); */
			return (0);
		}
		env = env->next;
	}
	//queremos agregar la nueva variable a la lista del export
	if (env_add_last(data, name, value, val))
		return (error_brk(data, "malloc", NULL, 12));
	return (0);
}
