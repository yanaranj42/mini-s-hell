/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:41:06 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/14 13:13:39 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*builtin. Todos estos son esquemas, ya que hay que meter los FD para las
redirecciones y mas cosas
*/
/*acabo de agregar los putstr para que imprima name=value*/
int	ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putstr_fd(env->name, 0);
		ft_putstr_fd(GREEN"="END, 0);
		ft_putendl_fd(env->value, 0);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value, 0);
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		printf(YELLOW"PWD: %s\n"END, cwd);
		return (SUCCESS);
	}
	return (FAIL);
}
/*busca */
static int	ft_strnum(char *s)
{
	int	flag;

	flag = 0;
	if (s == NULL)
		return (0);
	if (*s == '-')
		s++;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			flag = 1;
		else
		{
			flag = 0;
			break ;
		}
		s++;
	}
	return (flag);
}

void	ft_exit(t_general *data)
{
	char **argv;

	argv = data->first_token->argv;
	if (argv[1] && argv[2])
	{
		ft_putendl_fd("exit: minishell: Too many arguments", STDERR);
		data->ret_exit = 42;
	}
	else if (argv[1] && ft_strnum(argv[1]) == 0)
	{
		data->ret_exit = 666; //NO FA CAS
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(argv[1], STDERR);
		ft_putendl_fd(" numeric argument required", STDERR);
	}
	else if(argv[1])
		data->ret_exit = ft_atoi(argv[1]);
	exit(data->ret_exit);
}