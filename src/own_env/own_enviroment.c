/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_enviroment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:54:46 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/21 14:29:11 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	update_lvl(t_general *data)
{
	t_env	*env;
	char	*lvl;
	int		i;

	env = data->env_lst;
	while (env != NULL)
	{
		if (ft_strncmp(env->name, "SHLVL", 6) == 0)
		{
			i = ft_atoi(env->value);
			i++;
			if (i > 1000)
			{
				error_lvl(ft_itoa(i));
				i = 1;
			}
			else if (i < 0)
				i = 0;
			lvl = ft_itoa(i);
			free(env->value);
			env->value = lvl;
			return ;
		}
		env = env->next;
	}
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

int	fill_env_node(t_general *data, t_env *s_env, char **env, int i)
{
	s_env->name = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
	s_env->value = ft_strdup(getenv(s_env->name));
	s_env->hidden = 0;
	s_env->val = 1;
	s_env->next = NULL;
	if (!s_env->name || !s_env->value)
	{
		printf("Error: It's not possible to copy the enviroment\n");
		data->exit_status = 1;
		return (free_env(data->env_lst), 0);
	}
	return (1);
}

int	get_own_env(t_general *data, char **env)
{
	t_env	*s_env;
	int		i;

	i = -1;
	if (!env[0])
		set_empty_env(data);
	else
	{
		while (env[++i])
		{
			s_env = malloc(sizeof(t_env));
			if (!s_env)
				return (perror_message(NULL, "ENV creation failiure"), 0);
			if (fill_env_node(data, s_env, env, i) == 0)
				return (0);
			env_to_lst(data, s_env);
		}
		update_lvl(data);
	}
	return (1);
}
