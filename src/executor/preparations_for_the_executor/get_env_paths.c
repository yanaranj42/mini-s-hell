/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:28:30 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/21 18:46:34 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_env	*there_is_path(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->name, "PATH", 5) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	get_all_paths(t_env *env_lst, t_general *data)
{
	t_env	*path_node;

	path_node = there_is_path(env_lst);
	//if (path_node)
	if (path_node && path_node->value && path_node->value[0] != '\0')
	{
		data->paths = ft_split(path_node->value, ':');
		if (!data->paths)
		{
			free_xtkns_list(data);
			perror_message(NULL, "Malloc failure to get all paths");
			data->exit_status = 1;
			return (0);
		}
	}
	return (1);
}
