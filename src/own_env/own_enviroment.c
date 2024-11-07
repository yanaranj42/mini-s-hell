/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_enviroment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:54:46 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/07 16:31:23 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*COLOCAR ESTA FUNCION EN EL LIBFT y cambiar en todas las funciones donde se
	utilice ft_strncmp*/
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' && s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}

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
/*liberar en L49 dup de getenv
	agrego el hidden*/
int	get_own_env(t_general *data, char **env)
{
	t_env	*s_env;
	int		i;

	i = -1;
	if (!env)
		return (0); //Primero asegurarse de que hay env, antes de intentar recorrerlo
	while (env[++i])
	{
		s_env = malloc(sizeof(t_env));
		if (!s_env)
			return (perror_message(NULL, "Fail creating ENV"), 0);
		s_env->name = ft_strdup(ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]));
		s_env->value = ft_strdup(getenv(s_env->name));//obtiene el valor de la variable
		s_env->hidden = 0;
		s_env->next = NULL;
		env_to_lst(data, s_env);
		if (!s_env->name || !s_env->value)
			return (free_env(data->env_lst), 0);
			//FALTARIA EL MENSAJE DE ERROR, NO?
	}
	return (1);
}
/*	La idea de esta funcion es que, si no existe la var OLDPWD, PWD o HOME
	nos cree una en modo fantasma */
static int	exist_on_env(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (1);//existe
		env = env->next;
	}
	return (0);//no existe.
}

void	add_ghosts(t_general *data, char *value, int flag)
{
	data->equal = 1;
	if (!flag)
		flag = 0;
	if (!exist_on_env(data->env_lst, "OLDPWD") && flag == 1)
		add_upd_env(data, "OLDPWD_G", value);
	if (!exist_on_env(data->env_lst, "PWD") && flag == 0)
		add_upd_env(data, "PWD_G", value);
}
 