/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:44:50 by yaja              #+#    #+#             */
/*   Updated: 2024/11/20 01:00:02 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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
		if (ft_strncmp(env->name, var_name, len_env_name) == 0
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
	{
		new_env->value = ft_strdup("");
		new_env->val = 0;
	}
	else
	{
		new_env->value = ft_strdup(value);
		new_env->val = 1;
	}
	new_env->hidden = 0;
	new_env->next = NULL;
	env_to_lst(data, new_env);
	return (1);
}

void	add_upd_env(t_general *data, char *name, char *value)
{
	t_env	*env;

	if (value == NULL && data->equal == 1)//todas las null vars deben tener valor
		value = ft_strdup("");//LEAK AQUI
	env = data->env_lst;
	//printf("name2: %s - value2: [%s]\n", name, value);//BORRAR
	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0
			&& (ft_strlen(env->name) == ft_strlen(name)))
		{
			printf("hay match\n");
			if ((value || data->equal == 1))
			{
				free(env->value);
				env->value = ft_strdup(value);
				env->val = 1;
			}
		/* 	if (value && ft_strlen(value) == 0)
				free(value); */
			env->hidden = 0;
			printf("add_upd_env\tname:%s - value:%s - hid[%d] - val[%d]\n", env->name, env->value, env->hidden, env->val);//BORRAR
			return ;
			
		}
		env = env->next;
	}
	if (env_add_last(data, name, value) == 0)
		return ((void)error_brk(data, "malloc", NULL, 12));
	/* if (value && ft_strlen(value) == 0)
		free(value); */
}
