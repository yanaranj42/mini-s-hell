/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:23:55 by yanaranj          #+#    #+#             */
/*   Updated: 2024/08/19 16:07:53 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strnum(char *s);

//la flag -1 hace el exit
void    ft_exit(t_general *data)
{
	cases(data);
    if (data->flag == 1)
		;
	else if (data->flag == -1)
	{
		free_before_end(data);
		exit(data->ret_exit);
	}
}

static int	num_args(t_general *data)
{
	char	**argv;

	argv = data->first_token->argv;
	if ((argv[0] || argv[1]) && argv[2] == NULL)
	{
		if (argv[1])
			data->ret_exit = ft_atoi(argv[1]);
		return (1);
	}
	if (argv[2])
	{
		ft_putstr_fd("exit\n", STDERR);
		if (ft_strnum(argv[1]))
		{	
			data->flag = 1;
			data->ret_exit = 42;
			ft_putstr_fd("minishell: exit: Too many arguments\n", STDERR);
		}
		else
		{
			data->flag = -1;
			data->ret_exit = 155;
			ft_putstr_fd("minishell: exit: ", STDERR);
			ft_putstr_fd(argv[1], STDERR);
			ft_putendl_fd(" numeric argument required", STDERR);
		}
		free(argv[2]);
	}
	return (0);
}
void	cases(t_general *data)
{
	if (num_args(data))
		data->flag = -1;
}
/*
void	cases(t_general *data)
{
	char	**argv;

    data->flag = 0;
	argv = data->first_token->argv;
	while (**++argv)
	{
		if (argv[1] && argv[2])
		{
			if (ft_strnum(argv[1]) && argv[2]) //si el 1er av es num
			{
				data->flag = 1;
				break ;
			}
			else if (argv[1] && argv[2])
			{
				data->flag = -1;
				break ;
			}
			data->ret_exit = 42;
		}
		ft_putendl_fd("minishell: exit: Too many arguments", STDERR);
	}
	if (argv[1] && ft_strnum(argv[1]) == 0)
	{
		data->ret_exit = 666; //NO FA CAS
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(argv[1], STDERR);
		ft_putendl_fd(" numeric argument required", STDERR);
	}
	else if(argv[1])
		data->ret_exit = ft_atoi(argv[1]);
}*/

static int	ft_strnum(char *s)
{
	int	flag;

	flag = 0;
	if (s == NULL)
		return (0);
	if (*s == '-' || *s == '+')
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
