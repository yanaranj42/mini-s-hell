/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_empty_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 03:25:10 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 23:06:54 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	fill_path_env(t_general *data, char *name)
{
	t_env	*s_env;
	char	*tmp;

	s_env = malloc(sizeof(t_env));
	{
		if (!s_env)
			return (perror_message(NULL, ERR02), 0);
	}
	s_env->name = ft_strdup(name);
	tmp = ft_strjoin("/usr/local/sbin:", "/usr/local/sbin:/usr/local/bin:");
	if (!tmp)
		return (free_env(data->env_lst), 0);
	s_env->value = ft_strjoin(tmp, "/usr/sbin:/usr/bin:/sbin:/bin");
	s_env->hidden = 1;
	s_env->val = 1;
	s_env->next = NULL;
	if (!s_env->name || !s_env->value)
	{
		printf("Error: It's not possible to set the enviroment\n");
		data->exit_status = 1;
		free (tmp);
		return (free_env(data->env_lst), 0);
	}
	env_to_lst(data, s_env);
	free (tmp);
	return (1);
}

int	fill_oldpwd(t_general *data, char *name)
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
	s_env->val = 0;
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

int	fill_empty_env(t_general *data, char *name, char *value)
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
	s_env->val = 1;
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

int	set_empty_env(t_general *data)
{
	if (fill_empty_env(data, "PWD", NULL) == 0)
		return (0);
	if (fill_oldpwd(data, "OLDPWD") == 0)
		return (0);
	if (fill_path_env(data, "PATH") == 0)
		return (0);
	if (fill_empty_env(data, "SHLVL", "1") == 0)
		return (0);
	if (fill_empty_env(data, "_", "/usr/bin/env") == 0)
		return (0);
	return (1);
}
