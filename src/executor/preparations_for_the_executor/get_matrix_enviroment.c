/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matrix_enviroment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:28:49 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/18 15:28:19 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
//para reducir lineas podemos liberar la matrix y xtkns al  hacer un break 
int	fill_matrix(t_env *tmp, t_general *data, int *i)
{
	char	*half_str;
	
	half_str = NULL;
	while (tmp)
	{
		half_str = ft_strjoin(tmp->name, "=");
		if (!half_str)
			break ;
		if (!tmp->value && data->equal == 0)
			data->env_matrix[*i] = ft_strjoin(half_str, "");
		else 
			data->env_matrix[*i] = ft_strjoin(half_str, tmp->value);
		free(half_str);
		if (!data->env_matrix[*i])
		{
			printf(PURPLE"ERRROOOOOOR\n"END);//BORRAR
			break ;
		}
		(*i)++;
		tmp = tmp->next;
	}
	if (!half_str || !data->env_matrix[*i])
	{
		free_matrix_env(data);
		free_xtkns_list(data);
		return (0);
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
