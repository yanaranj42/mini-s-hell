/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:41:06 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/12 16:09:39 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*builtin. Para que cuando lo llame, me lo imprima. Esto es un esquema*/
int ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->value, 0);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value, 0);
	return (0);
}

int ft_pwd(void)
{
	char	cwd[PATH_MAX];
	
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (SUCCESS);
	}
	return (FAIL);
}