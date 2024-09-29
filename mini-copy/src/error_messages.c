/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:05:12 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/28 14:30:54 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "minishell.h"

// void	permission_denied(char *start)
// {
// 	printf("%s", "Permission denied: ");
// 	exit(126);
// }

// void	command_not_found(char *start)
// {
// 	printf("%s", "Command not found: ");
// 	exit(127);
// }

void	perror_message(char *start, char *message)
{
	if (start)
		printf("%s: ", start); 
	perror(message);
}
int	error_opt(char *s1, char *s2, char **arr, char *argv)
{
	ft_putstr_fd("minishell: export: `", STDOUT);
	ft_putstr_fd(s1, STDOUT);
	if (ft_strchr(argv, '='))
		ft_putstr_fd("=", STDOUT);
	if (s2 == NULL)
		s2 = ft_strdup("");
	ft_putstr_fd(s2, STDOUT);
	ft_putstr_fd(": not a valid identifier\n", STDOUT);
	arr_clean(arr);
	return (KO);
}
int	error_brk(t_general *data, char *msg, char *name, int flag)
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
	data->ret_exit = flag;
	free_exit(data);
	return (OK);
}