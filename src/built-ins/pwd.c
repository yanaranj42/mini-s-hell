/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:30:55 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/07 18:38:17 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];
	
	if (getcwd(cwd, PATH_MAX))
	{
		//ft_putendl_fd(cwd, 1);
		printf(BLUE"PWD: %s\n"END, cwd);
		return (1);
	}
	return (0);
}