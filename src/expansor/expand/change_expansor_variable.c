/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_expansor_variable.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/28 20:08:03 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	expand_final_value(t_xtkn *xtkn, t_env *env_tmp, int *i)
{
	if (env_tmp->value[*i] == '"')
	{
		xtkn->content = strjoinchar(xtkn->content, 30);
		if (!xtkn->content)
			return (0);
	}
	else if (env_tmp->value[*i] == '\'')
	{
		xtkn->content = strjoinchar(xtkn->content, 31);
		if (!xtkn->content)
			return (0);
	}
	else
	{
		xtkn->content = strjoinchar(xtkn->content, env_tmp->value[*i]);
		if (!xtkn->content)
			return (0);
	}
	return (1);
}

int	change_expansor_variable(t_xtkn *xtkn, char *tmp, t_env *env)
{
	t_env	*env_tmp;
	int		i;

	i = 0;
	env_tmp = env;
	if (!tmp)
		return (0);
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0))
		{
			while (env_tmp->value[i])
			{
				if (expand_final_value(xtkn, env_tmp, &i) == 0)
					return (0);
				i++;
			}
		}
		env_tmp = env_tmp->next;
	}
	return (1);
}
