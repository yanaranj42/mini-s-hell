/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:41:06 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/25 22:05:51 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->hidden == 0 && env->val == 1)
		{
			if (env->value)
			{
				ft_putstr_fd(env->name, 1);
				ft_putstr_fd("=", 1);
				ft_putendl_fd(env->value, 1);
			}
		}
		env = env->next;
	}
	return (0);
}
