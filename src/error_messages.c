/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaja <yaja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:05:12 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/02 14:54:46 by yaja             ###   ########.fr       */
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
//podemos poner directamente con el arr sin necesidad de pasar los otros dos
int	error_opt(char *s1, char *s2, char **arr)
{
	ft_putstr_fd("minishell: export: `", STDOUT);
	ft_putstr_fd(s1, STDOUT);
	ft_putstr_fd("=", STDOUT);
	ft_putstr_fd(s2, STDOUT);
	ft_putstr_fd(": not a valid identifier\n", STDOUT);
	arr_clean(arr, 0);
	return (OK);
}