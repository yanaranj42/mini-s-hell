/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_xtoken.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 06:39:18 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	put_new_list_xtoken_node(t_general *data, t_xtkn *xtkn)
{
	t_xtkn	*tmp_xtkn;

	if (!data->first_xtkn)
	{
		data->first_xtkn = xtkn;
		data->first_xtkn->back = NULL;
		data->first_xtkn->next = NULL;
	}
	else
	{
		tmp_xtkn = data->first_xtkn;
		while (tmp_xtkn && tmp_xtkn->next)
			tmp_xtkn = tmp_xtkn->next;
		tmp_xtkn->next = xtkn;
		xtkn->back = tmp_xtkn;
		xtkn->next = NULL;
	}
}

t_xtkn	*create_xtoken(void)
{
	t_xtkn	*new_xtkn;

	new_xtkn = malloc(sizeof(t_xtkn) * 1);
	if (!new_xtkn)
		return (NULL);
	return (new_xtkn);
}

t_xtkn	*token_to_xtoken(t_token *token, t_general *data)
{
	t_xtkn	*xtkn;

	xtkn = create_xtoken();
	if (!xtkn)
		return (0);
	xtkn->content = NULL;
	xtkn->type = token->type;
	put_new_list_xtoken_node(data, xtkn);
	return (xtkn);
}
