/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:44:50 by yaja              #+#    #+#             */
/*   Updated: 2024/09/17 16:19:59 by yanaranj         ###   ########.fr       */
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
	{
		printf("SOY CONCHA  ENTRO\n\n\n\n\n");
		value = ft_strdup("");
	}
	env = data->env_lst;
	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0 \
			&& (ft_strlen(env->name) == ft_strlen(name)))
		{
			printf(RED"Procedemos a borrar el valor: %s\n"END, env->value);
			if (env->value)
				free(env->value);
			if (value)
				env->value = ft_strdup(value);
			printf(GREEN"el nuevo valor es: %s\n"END, env->value);
		}
		env = env->next;
		//return (0);
	}
	//17/09 16:19 ESTAS AAQUI TIENES QUE HACER UNA CONDICION PARA QUE NO ENTRE AQUI SI HA HECHO EL WHILE
	if (env_add_last(data, name, value) == KO && )
		printf("AQUI VA ERROR\n");
	if(value && ft_strlen(value) == 0)
		free(value);
	return (0);
	//	return (error_brk(data, "malloc", NULL, 12));
}
