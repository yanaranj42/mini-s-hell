/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 04:15:09 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 02:16:37 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	*ft_memdel(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

char	**arr_clean(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr && arr[i] != NULL)
	{
		arr[i] = ft_memdel(arr[i]);
		i++;
	}
	arr = ft_memdel(arr);
	return (NULL);
}

void	free_exit(t_general *data)
{
	free(data->line);
	printf("status7: %i\n", data->exit_status);
	exit(data->exit_status);
}
