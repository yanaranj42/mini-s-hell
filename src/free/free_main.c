/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/19 20:29:34 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_env(t_env *head)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = head;
	while (tmp)
	{
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
		prev = NULL;
	}
}

void	free_before_next_round(t_general *data)
{
	// free_tokens_list(data);
	// free_xtkns_list(data);
	free_matrix_env(data);
	free_cmd(data);
	free_data_paths(data);
	free(data->line);
	data->line = NULL;
}
