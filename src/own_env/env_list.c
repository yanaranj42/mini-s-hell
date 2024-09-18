/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:44:50 by yaja              #+#    #+#             */
/*   Updated: 2024/09/18 20:21:22 by yanaranj         ###   ########.fr       */
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
	
	if (!var_name)
		return (NULL);
	env = data->env_lst;
	len_var_name = ft_strlen(var_name);
	while (env != NULL)
	{
		len_env_name = ft_strlen(env->name);
		if (ft_strncmp(env->name, var_name, len_env_name) == 0 \
			&& (len_env_name == len_var_name))
		{
			//printf("match found on variable: %i %s\n", i, env->name);
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

int	env_add_last(t_general *data, char *name, char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (KO);
	new_env->name = ft_strdup(name);//creamos un nuevo nodo en la lista de env
	if (data->equal == KO)
		new_env->value = NULL;
	else
		new_env->value = ft_strdup(value);//hara un dup de "" como value
	new_env->next = NULL;
	/* if (!new_env->name || val == 0)
	{
		//enviar flag de val para indicar que esta variable no se ha de imprimir en el env
		printf(BLUE"no tenemos valor en la variable\n");
		env_to_lst(data, new_env);
		print_env(new_env, val);
		printf("no tenemos valor en la variable\n"END);
		return (KO);
	 }*/
	env_to_lst(data, new_env);//add new var to env lst
	printf("NEW VAR ON ENV  LST\n");
	print_env(data, new_env);
	data->equal = OK;
	return (OK);
}
/*	CASOS:
*	variable ya existente: USER
*		export				--> USER="yanaranj"
*		export USER+=Pingu 	--> USER="yanaranjPingu"
*	variable que no existe: Z
*		export Z			--> Z
*		export Z+=			--> Z=""
*		export Z+=newVar	--> Z="newVar"
*	casos en comun: VAR
*		export VAR= 		--> VAR=""
*/
//tenmos que liberar el dup al salir.
int	add_upd_env(t_general *data, char *name, char *value)
{
	t_env	*env;

	if (value == NULL && data->equal == OK)
		value = ft_strdup("");
	env = data->env_lst;
	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0 \
			&& (ft_strlen(env->name) == ft_strlen(name)))
		{
			if ((value ||  data->equal == OK))
			{
				if (env->value != NULL)
				{
					free(env->value);
				}
				if (value)
					env->value = ft_strdup(value);
			}
			//SI RECIBE a, COMO LA VAR YA EXISTE, ME BORRA EL VALOR. HAY QUE CORREGIR
				//env->value = ft_strdup("");
			if(value && ft_strlen(value) == 0)
				free(value);
			return (0);
		}
		env = env->next;
	}
	if (env_add_last(data, name, value) == KO)
		return (error_brk(data, "malloc", NULL, 12));
	if(value && ft_strlen(value) == 0)
		free(value);
	return (0);
}
