/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:23:55 by yanaranj          #+#    #+#             */
/*   Updated: 2024/08/22 15:11:29 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strnum(char *s, int i);
static void	exit_code(t_general *data);
static int	check_long(char *arg);

void	ft_exit(t_general *data)
{
	ft_putstr_fd("exit \n", STDERR);
	if (data->first_token->argv[0] && data->first_token->argv[1] == NULL)
		exit(0);
	exit_code(data);
	if (data->exit_flag == 1)
		;
	else if(data->exit_flag == -1)
		exit(data->ret_exit);
	//TENEMOS QUE LIBERAR EL READLINE
}

static int	valid_arg(char *argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return (0);
	while (argv[i] == ' ')
		i++;
	if (argv[i] == '-' || argv[i] == '+')
		i++;
	while (argv[i] == '0')
		i++;
	if (ft_strnum(argv, i))
		return (1);
	return (0);
}
static void	exit_code(t_general *data)
{
	char	**argv;

	argv = data->first_token->argv;
	data->exit_flag = -1;
	if (valid_arg(argv[1]) == 0)
	{
		ft_putstr_fd(argv[1], STDERR);
		ft_putendl_fd(" numeric arg required", STDERR);
		data->ret_exit = 99;
	}
	else
	{
		data->exit_flag = -1;
		if (check_long(argv[1]))
			data->ret_exit = 50;
		else
			data->ret_exit = ft_atoi(argv[1]);
	}
	if (argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
		data->exit_flag = 1;
		data->ret_exit = 155;
	}
}

static int	ft_strnum(char *s, int i)
{
	int	flag;

	flag = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			flag = 1;
		else
		{
			flag = 0;
			break ;
		}
		i++;
	}
	return (flag);
}

static int	check_long(char *argv)
{
	int	len;

	len = ft_strlen(argv);
	if (len > 19)
	{
		if (argv[0] == '-' && ft_strncmp(argv, "-9223372036854775807", len) == 0)
			return (1);
		else if (argv[0] == '+' && ft_strncmp(argv, "+9223372036854775807", len) == 0)
			return (1);
	}
	else
	{
		if (ft_strncmp(argv, "9223372036854775807", len) ==  0)
			return (1);
	}
	return (0);
}
