/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:41:06 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/27 12:05:34 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*builtin. Todos estos son esquemas, ya que hay que meter los FD para las
redirecciones y mas cosas
*/
/*tiene que salir por e STDOUT*/
int	ft_env(t_env *env)
{
	printf(YELLOW"OUR ENVIRONMENT\n"END);
	while (env && env->next != NULL)
	{
		ft_putstr_fd(env->name, 1);
		ft_putstr_fd(GREEN"="END, 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value, 1);
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		printf(BLUE"PWD: %s\n"END, cwd);
		return (SUCCESS);
	}
	return (FAIL);
}
/*busca */

