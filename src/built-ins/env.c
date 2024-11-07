/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:41:06 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/07 12:54:59 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*tiene que salir por e STDOUT*/
/* int	ft_env(t_env *env)
{
	printf(YELLOW"OWN ENVIRONMENT\n\n"END);
	while (env)
	{
		if (env->value && ft_strcmp("OLDPWD_G", env->name) != 0)
		{
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(env->value, 1);
		}
		env = env->next;
	}
	 if (env)
	{
		if(!env->value)
			return (0);
		else
		{
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(env->value, 1);
		}
	} 
	return (0);
} */

int	ft_env(t_env *env)
{
	printf(YELLOW"OWN ENVIRONMENT\n\n"END);
	while (env)
	{
		if (env->hidden == 0)
		{
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(env->value, 1);
		}
		env = env->next;
	}
	return (0);
}
