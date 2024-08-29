/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:28:30 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/29 21:27:27 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_env *there_is_path(t_env	*env_lst)
{
	t_env *tmp;

	tmp = env_lst;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->name, "PATH", 5) == 0) //poniendo que compare 5 posiciones me aseguro que detras de path no haya nada mas no?
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	get_all_paths(t_env	*env_lst, t_general *data)
{
	t_env *path_node;

	path_node = there_is_path(env_lst);
	if (path_node)
	{
		data->paths = ft_split(path_node->value, ':');
		if (!data->paths)
		{
			perror_message(NULL, "Malloc failure in take path");
			return (0);
		}
	}
	return (1);
}

