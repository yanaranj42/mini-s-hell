/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:03:39 by yanaranj          #+#    #+#             */
/*   Updated: 2024/10/17 15:33:41 by yanaranj         ###   ########.fr       */
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