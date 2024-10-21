/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:03:39 by yanaranj          #+#    #+#             */
/*   Updated: 2024/10/21 15:29:29 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	set_oldpwd(t_general *data)
{
    char	old_value[PATH_MAX];

	data->equal = 1;
	getcwd(old_value, PATH_MAX);
	env_add_last(data, "OLDPWD", old_value);
}


int	check_dir(char *path)
{
	struct stat	stats;
	
	if (stat(path, &stats) == 0)
	{
		if (S_ISDIR(stats.st_mode))
			return (1);
	}
	return (0); //No existe o no es un directory
}

int	error_dir(t_general *data, char *path)
{
	ft_putstr_fd("minishell: cd: ", STDOUT);
	ft_putstr_fd(path, STDOUT);
	ft_putstr_fd(": No such file or directory\n", STDOUT);
	data->exit_status = 1;
	return (0);
}