/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:41:06 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/10 00:22:32 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*tiene que salir por e STDOUT*/
int	ft_env(t_env *env)
{
	printf(YELLOW"OWN ENVIRONMENT\n\n"END);
	printf("\n"); //BORRAR
	while (env && env->next != NULL)
	{
		ft_putstr_fd(env->name, 1);
		ft_putstr_fd(GREEN"="END, 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	if (env)
	{
		ft_putstr_fd(env->name, 1);
		ft_putstr_fd(GREEN"="END, 1);
		ft_putendl_fd(env->value, 1);
	}
	return (0);
}
