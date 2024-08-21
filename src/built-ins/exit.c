/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:23:55 by yanaranj          #+#    #+#             */
/*   Updated: 2024/08/21 13:49:12 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strnum(char *s);
static void	exit_code(t_general *data);
//static int	check_long(char *argv);

void	ft_exit(t_general *data)
{
	ft_putstr_fd("exit \n", STDERR);
	if (data->first_token->argv[0] && data->first_token->argv[1] == NULL)
		exit(0);
	exit_code(data);
	if (data->flag == 1)
		;
	else if(data->flag == -1)
		exit(data->ret_exit);
	//TENEMOS QUE LIBERAR EL READLINE
}

static int	valid_arg(char *argv)
{
	int	i;

	i = 0;
	if (ft_strnum(argv) == 0)
	{
		printf(RED"%s INVALID ARG\n"END, argv);
		return (0);
	}
	printf(GREEN"%s VALID ARG\n"END, argv);
	return (1);
}
/*PONER LAS FLAGS*/
static void	exit_code(t_general *data)
{
	char	**argv;

	argv = data->first_token->argv;
	/*if (check_long(argv[1]) == 1)
	{
		printf("SIp\n");
		data->flag = -1;
		data->ret_exit = 88;
	}*/
	if (!valid_arg(argv[1]))
	{
		ft_putstr_fd(argv[1], STDERR);
		ft_putendl_fd(" numeric arg required", STDERR);
		data->flag =  -1;
		data->ret_exit = 99;
	}
	else
	{
		printf("NOp\n");
		data->flag = -1;
		data->ret_exit = ft_atoi(argv[1]);
	}
	if (argv[1] && argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
		data->flag = 1;
		data->ret_exit = 155;
	}
}

static int	ft_strnum(char *s)
{
	int	flag;

	flag = 0;
	if (s == NULL)
		return (0);
	while (*s == ' ') //control  de espacios
		s++;
	if (*s == '-' || *s == '+') //control de signo
		s++;
	while (*s == '0') //control de zeros
		s++;
	while (*s) //en busca de args !nums
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
/*static int	check_long(char *argv)
{
	if  (argv[0] == '-' || argv[0] == '+')
	{
		if (ft_strncmp(argv, (char *)LONG_MIN, 19) > 0)
			printf(BLUE"%s: IS LONG MIN\n", argv);
		else if (ft_strncmp(argv, (char *)LONG_MAX, 19) > 0)
			printf(BLUE"%s: IS LONG MAX\n", argv);
		return (1);
	}
	return (0);
}*/