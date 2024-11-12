/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 04:15:09 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 04:16:31 by mfontser         ###   ########.fr       */
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

void	unset_free(t_env *env)
{
	ft_memdel(env->name);
	ft_memdel(env->value);
	ft_memdel(env);
}

void	free_exit(t_general *data)
{
	free(data->line);
	exit(data->exit_status);
}
