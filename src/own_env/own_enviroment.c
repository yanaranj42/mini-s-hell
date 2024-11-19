/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_enviroment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:54:46 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/19 13:31:45 by yanaranj         ###   ########.fr       */
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

int fill_empty_env(t_general *data, char *name, char *value)
{
	t_env	*s_env;

	s_env = malloc(sizeof(t_env));
	{
		if (!s_env)
			return (perror_message(NULL, ERR02), 0);
	}
	s_env->name = ft_strdup(name);
	if (name[0] == 'P')
		s_env->value = getcwd(NULL, 0);
	else
		s_env->value = ft_strdup(value);
	s_env->hidden = 0;
	s_env->next = NULL;
	if (!s_env->name || !s_env->value)
	{
		printf("Error: It's not possible to set the enviroment\n");
		data->exit_status = 1;
		return (free_env(data->env_lst), 0);
	}
	env_to_lst(data, s_env);
	return (1);
}

int fill_oldpwd(t_general *data, char *name)
{
	t_env	*s_env;

	s_env = malloc(sizeof(t_env));
	{
		if (!s_env)
			return (perror_message(NULL, ERR02), 0);
	}
	s_env->name = ft_strdup(name);
	s_env->value = getcwd(NULL, 0);
	s_env->hidden = 1;
	s_env->next = NULL;
	if (!s_env->name || !s_env->value)
	{
		printf("Error: It's not possible to set the enviroment\n");
		data->exit_status = 1;
		return (free_env(data->env_lst), 0);
	}
	env_to_lst(data, s_env);
	return (1);
}



int set_empty_env(t_general *data)
{
	if (fill_empty_env(data, "PWD", NULL) == 0)
		return (0);
	if (fill_oldpwd(data, "OLDPWD") == 0)
		return (0);
	if (fill_empty_env(data, "LS_COLORS", "\0") == 0)
		return (0);
	if (fill_empty_env(data, "LESSCLOSE", "/usr/bin/lesspipe %s %s") == 0)
		return (0);
	if (fill_empty_env(data, "LESSOPEN", "| /usr/bin/lesspipe %s") == 0)
		return (0);
	if (fill_empty_env(data, "SHLVL", "1") == 0)
		return (0);
	if (fill_empty_env(data, "_", "/usr/bin/env") == 0)
		return (0);
	return (1);
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
	printf("env_to_lst\tname:%s - value:%s - hid[%d] - val[%d]\n", my_env->name, my_env->value, my_env->hidden, my_env->val);//BORRAR
	tmp->next = my_env;
}
/*recibir el i por param para cortar lines*/
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
				return (perror_message(NULL, ERR02), 0);
			s_env->name = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
			s_env->value = ft_strdup(getenv(s_env->name));
			s_env->hidden = 0;
			s_env->val = 1;//siempre inicia con 1 aunqu esta no tenga valor
			s_env->next = NULL;
			if (!s_env->name || !s_env->value)
			{
				printf("Error: It's not possible to copy the enviroment\n");
				data->exit_status = 1;
				return (free_env(data->env_lst), 0);
			}
			env_to_lst(data, s_env);
		}
		update_lvl(data);
	}
	return (1);
}
