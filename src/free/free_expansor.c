/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_expansor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 04:21:08 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 04:22:26 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_splited_content(char **content)
{
	int	i;

	i = 0;
	if (content == NULL)
		return ;
	while (content[i])
	{
		free(content[i]);
		i++;
	}
	free(content);
	content = NULL;
}

void	free_expansor(t_general *data)
{
	data->exit_status = 1;
	free_tokens_list(data);
	free_xtkns_list(data);
}
