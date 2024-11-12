/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansor_variable_exists.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 06:19:23 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	check_expansor_variable_exists(char *tmp, t_env *env)
{
	t_env	*env_tmp;

	env_tmp = env;
	if (!tmp)
		return (0);
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0)
			&& env_tmp->hidden == 0)
			return (1);
		env_tmp = env_tmp->next;
	}
	return (0);
}
