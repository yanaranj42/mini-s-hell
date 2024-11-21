/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_error_messages.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:05:12 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/21 02:51:55 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	error_cd_last(t_general *data, char c, int flag)
{
	if (flag == 1)
	{
		write(2, RED, ft_strlen(RED));
		ft_putstr_fd("💀 minishell: cd: -", STDERR);
		ft_putchar_fd(c, STDERR);
		ft_putstr_fd(": invalid option\n", STDERR);
		write(2, END, ft_strlen(END));
		data->exit_status = 2;
	}
	if (flag == 0)
	{
		write(2, RED, ft_strlen(RED));
		ft_putstr_fd("💀 minishell: cd: ", STDERR);
		ft_putstr_fd("too many arguments\n", STDERR);
		write(2, END, ft_strlen(END));
		data->exit_status = 1;
	}
	return (data->exit_status);
}

int	error_env(void)
{
	write(2, RED, ft_strlen(RED));
	ft_putstr_fd("💀 minishell: env:", STDERR);
	ft_putstr_fd(" No such file or directory\n", STDERR);
	write(2, END, ft_strlen(END));
	return (127);
}

int	error_opt(char *s1, char *s2, char **arr, char *argv)
{
	write(2, RED, ft_strlen(RED));
	ft_putstr_fd("💀 minishell: export: `", STDERR);
	ft_putstr_fd(s1, STDERR);
	if (ft_strchr(argv, '='))
		ft_putstr_fd("=", STDERR);
	if (s2 == NULL)
		s2 = ft_strdup("");
	ft_putstr_fd(s2, STDERR);
	ft_putstr_fd(": not a valid identifier\n", STDERR);
	write(2, END, ft_strlen(END));
	free(s2);
	arr_clean(arr);
	return (1);
}

void	error_brk(t_general *data, char *msg, char *name, int flag)
{
	write(2, RED, ft_strlen(RED));
	if (name || msg)
		ft_putstr_fd("💀 minishell: ", STDERR);
	if ((flag == 1 && *name && !msg) || flag == 12 || flag == 14)
		perror(name);
	else if (name)
	{
		ft_putstr_fd(name, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (msg)
	{
		ft_putstr_fd(msg, STDERR);
		ft_putstr_fd("\n", STDERR);
	}
	write(2, END, ft_strlen(END));
	data->exit_status = flag;
	free_exit(data);
}
