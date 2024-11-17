/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_xtkn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/06 16:10:49 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_xtkn	*expand_xtkn(t_token *token, t_general *data)
{
	t_xtkn	*xtkn;

	xtkn = token_to_xtoken(token, data);
	if (!xtkn)
	{
		printf("Error: There have been problems creating expanded tokens\n");
		return (NULL);
	}
	if (build_expanded_content(xtkn, token, data) == 0)
	{
		printf("Error:\n");
		printf("It's not possible to build the expanded tokens content\n");
		return (NULL);
	}
	return (xtkn);
}
