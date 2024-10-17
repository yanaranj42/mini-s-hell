/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:44:50 by yaja              #+#    #+#             */
/*   Updated: 2024/10/17 15:47:46 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	env_add_last(t_general *data, char *name, char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (0);
	new_env->name = ft_strdup(name);
	if (data->equal == 0)
		new_env->value = NULL; 
	else
		new_env->value = ft_strdup(value);
	new_env->next = NULL;
	env_to_lst(data, new_env);
//liberar el value y el name para evitar errores de leaks
	return (1);
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
void	add_upd_env(t_general *data, char *name, char *value)
{
	t_env	*env;

	if (value == NULL && data->equal == 1)
		value = ft_strdup("");
	env = data->env_lst;
	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0 \
			&& (ft_strlen(env->name) == ft_strlen(name)))
		{
			if ((value || data->equal == 1))
			{
				free(env->value);
				env->value = ft_strdup(value);
			}
			if(value && ft_strlen(value) == 0)
				free(value);
			return ;
		}
		env = env->next;
	}
	if (env_add_last(data, name, value) == 0)
		return ((void)error_brk(data, "malloc", NULL, 12));
	if(value && ft_strlen(value) == 0)
		free(value);
}