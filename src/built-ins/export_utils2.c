/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:44:50 by yaja              #+#    #+#             */
/*   Updated: 2024/11/22 14:54:09 by mfontser         ###   ########.fr       */
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
	while (env)
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

void	upd_node(t_env *env, char *old_value, char *value, int equal)
{
	char	*old_val;

	if (!equal)
	{
		old_val = old_value;
		env->value = ft_strjoin(old_value, value);
		env->val = 1;
		free(old_val);
	}
	else if (value || equal)
	{
		free(env->value);
		env->value = ft_strdup(value);
		env->val = 1;
	}
	env->hidden = 0;
}

void loop_add_upd_env (t_general *data, char *name, t_env	*env, char **value) // DA SEGFAULT - REVISAR QUE ESTE LLEGANDO TODO BIEN
{
	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 0
			&& (ft_strlen(env->name) == ft_strlen(name)))
		{
			if (env->value)
			{
				free(env->value);
				env->value = NULL;
			}
			upd_node(env, NULL, *value, data->equal);
			free(*value);
			*value = NULL;
			return ;
		}
		env = env->next;
	}
}

void	add_upd_env(t_general *data, char *name, char **value)
{
	t_env	*env;

	if (ft_strncmp(name, "_", 1) == 0)
		return ;
	if (*value == NULL && data->equal == 1)
		*value = ft_strdup("");
	env = data->env_lst;
	
	loop_add_upd_env (data, name, env, value);


	if (env_add_last(data, name, *value) == 0)
		return ((void)error_brk(data, "malloc", NULL, 12));
	if (!(*value) || ft_strncmp(*value, "", 1) == 0)
	{
		free(*value);
		*value = NULL;
	}
}
