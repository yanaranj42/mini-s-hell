/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_enviroment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:54:46 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/12 12:48:56 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
/* cada nodo que vayamos obteniendo al hacer la copia del env, lo agregamos y
creamos una nuestra lista. */
void env_to_lst(t_general *data, t_env *my_env)
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
			return (perror_message(NULL, "Fail in env creation"), 0);
		s_env->name = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		s_env->value = ft_strdup(getenv(s_env->name));
		s_env->next = NULL;
		env_to_lst(data, s_env);
		if (!s_env->name || !s_env->value)
			return (free_env(data->env_lst), 0);
		printf("%s = %s\n", s_env->name, s_env->value);
	}
	return (1);
}
