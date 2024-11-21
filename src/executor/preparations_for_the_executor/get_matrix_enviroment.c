/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matrix_enviroment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:28:49 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/21 19:23:59 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_things(t_general *data)
{
	free_xtkns_list(data);
	free_matrix_env(data);
}

int	fill_matrix(t_env *tmp, t_general *data, int *i)
{
	char	*half_str;

	while (tmp)
	{
		half_str = ft_strjoin(tmp->name, "=");
		if (!half_str)
		{
			free_things(data);
			return (0);
		}
		if (!tmp->value)
			data->env_matrix[*i] = ft_strjoin(half_str, "");
		else
			data->env_matrix[*i] = ft_strjoin(half_str, tmp->value);
		if (!data->env_matrix[*i])
		{
			free(half_str);
			free_things(data);
			return (0);
		}
		free(half_str);
		(*i)++;
		tmp = tmp->next;
	}
	return (1);
}

int	env_matrix_base(t_env *env_lst)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env_lst;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int	get_matrix_env(t_general *data, t_env *env_lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env_lst;
	if (tmp)
	{
		data->env_matrix = malloc(sizeof(char *) * (env_matrix_base(env_lst)
					+ 1));
		if (!data->env_matrix)
		{
			free_xtkns_list(data);
			return (0);
		}
		if (fill_matrix(tmp, data, &i) == 0)
			return (0);
		data->env_matrix[i] = NULL;
	}
	return (1);
}
