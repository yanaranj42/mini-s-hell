/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 04:15:09 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/22 14:48:23 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		if (split[i])
		{
			free(split[i]);
		}
		i++;
	}
	free(split);
}

void	*ft_memdel(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	return (NULL);
}

void	arr_clean(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i] != NULL)
	{
		arr[i] = ft_memdel(arr[i]);
		arr[i] = NULL;
		i++;
	}
	arr = ft_memdel(arr);
	arr = NULL;
}

void	free_exit(t_general *data)
{
	free(data->line);
	exit(data->exit_status);
}
