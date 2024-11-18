/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:41:06 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/18 11:48:11 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
//	BORRAR AQUI
/* static void print_matrix_env(char **env_matrix)
{
	int i;

	i = 0;
	while (env_matrix[i])
	{
		printf("[%i]\t%s\n",i, env_matrix[i]);
		i++;
	}
} */
/* int	ft_env(t_env *env, t_general *data)
{
	//printf(YELLOW "OWN ENVIRONMENT\n" END);
	//print_matrix_env(data->env_matrix);
	(void)data;
	while (env)
	{
		if (env->hidden == 0)
		{
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(env->value, 1);
			//printf("valor---> %s\n", env->value);
		}
		env = env->next;
	}
	return (0);
} */

int	ft_env(t_env *env)
{
	int	i = 0;
	printf(YELLOW"OWN ENVIRONMENT\n\n"END);
	while (env && env->next != NULL)
	{
		if (env->value && env->hidden == 0)
		{
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(env->value, 1);
		}
		env = env->next;
		i++;
	}
	if (env)
	{
		if(!env->value)
			return (0);
		else if (env->value && env->hidden == 0)
		{
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(env->value, 1);
		}
	}
	return (0);
}