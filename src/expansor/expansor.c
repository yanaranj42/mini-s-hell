/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/06 16:14:11 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	start_xtkns(t_general *data)
{
	t_token	*token;
	t_xtkn	*xtkn;

	token = data->first_token;
	while (token)
	{
		xtkn = expand_xtkn(token, data);
		if (!xtkn)
			return (0);
		if (xtkn->content)
		{
			if (split_xtkn(xtkn, data) == 0)
				return (0);
		}
		else
		{
			if (xtkn->back)
				xtkn->back->next = NULL;
			free(xtkn);
			xtkn = NULL;
		}
		token = token->next;
	}
	return (1);
}

int	expansor(t_general *data)
{
	if (start_xtkns(data) == 0)
	{
		free_expansor(data);
		return (0);
	}
	if (finish_xtkns(data->first_xtkn, data) == 0)
	{
		free_expansor(data);
		return (0);
	}
	free_tokens_list(data);
	return (1);
}
