/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:41:00 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/21 01:22:32 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	args_counter(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

static int	n_flag(char *argv)
{
	int	i;

	i = 0;
	if (argv[0] == '-')
		i++;
	while (argv[i] == 'n')
		i++;
	if (argv[i] != '\0')
		return (0);
	return (1);
}

int	ft_echo(char **argv, t_general *data)
{
	int	i;
	int	n_opt;

	i = 1;
	n_opt = 0;
	if (args_counter(argv) > 1)
	{
		while (argv[i] && ft_strchr(&argv[i++][0], '-'))
		{
			if (!n_flag(argv[i]))
				break ;
			n_opt = 1;
		}
		while (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1])
				write(1, " ", 1);
			i++;
		}
		if (n_opt == 0)
			write(1, "\n", 1);
	}
	data->exit_status = 0;
	return (1);
}
