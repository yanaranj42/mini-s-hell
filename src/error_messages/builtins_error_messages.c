/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_error_messages.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:05:12 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 13:39:53 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	error_cd_last(t_general *data, char c, int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd("minishell: cd: -", STDOUT);
		ft_putchar_fd(c, STDERR);
		ft_putstr_fd(": invalid option", STDOUT);
		data->exit_status = 1;
	}
	if (flag == 0)
	{
		ft_putstr_fd("minishell: cd: ", STDOUT);
		ft_putstr_fd("too many arguments", STDOUT);
		data->exit_status = 2;
	}
	ft_putendl_fd("\n", STDOUT);
	return (0);
}

int error_opt(char *s1, char *s2, char **arr, char *argv)
{
    ft_putstr_fd("minishell: export: `", STDOUT);
    ft_putstr_fd(s1, STDOUT);
    if (ft_strchr(argv, '='))
        ft_putstr_fd("=", STDOUT);
    if (s2 == NULL)
        s2 = ft_strdup("");
    ft_putstr_fd(s2, STDOUT);
    ft_putstr_fd(": not a valid identifier\n", STDOUT);
    free(s2);
    arr_clean(arr);
    return (1);
}

void	error_brk(t_general *data, char *msg, char *name, int flag)
{
	if (name || msg)
		ft_putstr_fd("minishell: ", STDERR);
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
	data->exit_status = flag;
	free_exit(data);
}
