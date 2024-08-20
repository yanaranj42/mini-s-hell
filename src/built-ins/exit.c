/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:23:55 by yanaranj          #+#    #+#             */
/*   Updated: 2024/08/20 12:46:42 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strnum(char *s);

//la flag -1 hace el exit
//la flag 1 se mantiene en el programa
void    ft_exit(t_general *data)
{
	ft_putstr_fd("exit\n", STDERR);
	cases(data);
    if (data->flag == 1)
		;
	else if (data->flag == -1)
	{
		//free_before_end(data);
		exit(data->ret_exit);
	}
}

static int	num_args(t_general *data)
{
	char	**argv;

	argv = data->first_token->argv;
	if (argv[0] || argv[1])
	{
		if (argv[1] && !argv[2])
			return (data->ret_exit = ft_atoi(argv[1]), 1);
	}
	if (argv[2])
	{
		if (ft_strnum(argv[1]))
		{
			ft_putstr_fd("minishell: exit: Too many arguments\n", STDERR);
			return ((data->ret_exit = 42), 0);
		}
		else
		{
			ft_putstr_fd("minishell: exit: ", STDERR);
			ft_putstr_fd(argv[1], STDERR);
			ft_putendl_fd(" numeric argument required", STDERR);
			return ((data->ret_exit = 155), 1);
		}
	}
	return (0);
}

static int	large_num(t_general *data)
{
	int		len;
	char	**argv;

	argv = data->first_token->argv;
	len = ft_strlen((char *)argv[1]);
	if (len == 20)
	{
		if (argv[1][0] == '-' || argv[1][0] == '+')
		{
			if (ft_strncmp((char *)LONG_MIN, argv[1], 20) == 0)
				printf(YELLOW"LONG_MIN\n"END);
			else if(ft_strncmp((char *)LONG_MAX, argv[1], 19)  == 0)
				printf(BLUE"LONG MAX\n"END);			
		}
		return (1);
	}
	return (0);
}
//check la posicion de la flag porque siempre sale con -1
void	cases(t_general *data)
{

	if (num_args(data))
		data->flag = -1;
	else
		data->flag = 1;
	if (large_num(data))
		data->flag = -1;
}

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
