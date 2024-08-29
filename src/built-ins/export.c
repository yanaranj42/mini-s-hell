/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:44:12 by yanaranj          #+#    #+#             */
/*   Updated: 2024/08/29 16:06:17 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_export(t_general *data)
{
	char	**argv; //cmd
	t_env	tmp_env;

	argv = data->first_token->argv;
	tmp_env = data->env_lst;
}