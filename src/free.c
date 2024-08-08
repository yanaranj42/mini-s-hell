/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/08 00:52:42 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "minishell.h"


void	free_env(t_general *data)
{
	int	i;

	i = 0;
	if (data->own_env == NULL)
		return ;
	while (data->own_env[i])
	{
		free(data->own_env[i]);
		i++;
	}
	free(data->own_env);
}


void	free_before_end(t_general *data)
{
	free_env(data);
}
