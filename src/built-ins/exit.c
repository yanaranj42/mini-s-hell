/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:23:55 by yanaranj          #+#    #+#             */
/*   Updated: 2024/09/23 15:46:51 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	ft_strnum(char *s, int i);
static int	exit_code(t_general *data, char **argv);
static int	check_long(char *arg);
/* El error de salida de LONG_MIN es bash, es 1... que fem??*/
void	ft_exit(t_general *data)
{
	printf (ORANGE"    Fire can't kill a dragon ❤️‍🔥\n"END);
	printf (CYAN"              But.... Winter is coming ❄️\n\n"END);
	ft_putstr_fd("exit \n", STDERR);
	if (data->first_cmd->argv[0] && data->first_cmd->argv[1] == NULL)
		exit(0);
	if (exit_code(data, data->first_cmd->argv) == 1)
		;
	else
		free_exit(data);
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
static int	exit_code(t_general *data, char **argv)
{
	printf("LEN: %zu\n", ft_strlen(argv[1]));
	if (valid_arg(argv[1]) && ft_strlen(argv[1]) < 21)
	{
		if (argv[2])
		{
			ft_putendl_fd(CYAN"minishell: exit: too many arguments"END, STDERR);
			data->ret_exit = 155;
			return (1);
		}
		else
		{	
			if (check_long(argv[1]))
				data->ret_exit = 255;
			else
				data->ret_exit = ft_atoi(argv[1]);
			return (0);
		}
	}
	else
	{
		ft_putstr_fd("minishell: exit: " , STDERR);
		ft_putstr_fd(argv[1], STDERR);
		ft_putendl_fd(RED": numeric arg required"END, STDERR);
		data->ret_exit = 2;
	}
	return (0);
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
	if (len == 20)
	{
		printf(YELLOW"IS LONG SIGN NUM\n"END);
		if (argv[0] == '-' && ft_strncmp(argv, "-9223372036854775807", len) == 0)
			return (1);
		else if (argv[0] == '+' && ft_strncmp(argv, "+9223372036854775807", len) == 0)
			return (1);
	}
	else
	{
		if (ft_strncmp(argv, "9223372036854775807", len) ==  0)
		{
			printf(BLUE"IS LONG NO SIGN NUM\n"END);
			return (1);
		}
	}
	return (0);
}
