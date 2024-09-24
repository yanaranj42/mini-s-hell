/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:28:30 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/24 17:51:22 by yanaranj         ###   ########.fr       */
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
	int i = 0; //BORRAR

	path_node = there_is_path(env_lst);
	if (path_node)
	{
		data->paths = ft_split(path_node->value, ':');
		if (!data->paths)
		{
			perror_message(NULL, "Malloc failure in take path");
			return (0);
		}
		//BORRAR FINAL
		printf ("# Get path \n\n Los paths del env son:\n");
		while (data->paths[i])
		{
			printf("    %s\n", data->paths[i]);
			i++;
		}
	}
	return (1);
}

