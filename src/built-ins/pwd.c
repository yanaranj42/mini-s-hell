/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:30:55 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/20 02:55:24 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_pwd(t_env *env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putstr_fd(cwd, 0);
		ft_putendl_fd("", 1);
		return (1);
	}
	else
	{
		while (env)
		{
			if (ft_strncmp(env->name, "PWD", 3) == 0)
			{
				ft_putstr_fd(env->value, 1);
				ft_putendl_fd("\n", 1);
				return (1);
			}
			env = env->next;
		}
	}
	return (0);
}
