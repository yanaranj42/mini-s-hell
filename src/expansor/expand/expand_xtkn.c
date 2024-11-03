/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_xtkn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/28 20:30:23 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_xtkn *expand_xtkn(t_token *token, t_env *env, t_general *data)
{
	t_xtkn	*xtkn;

	xtkn = token_to_xtoken(token, data);
	if (!xtkn)
	{
		printf("Error: There have been problems creating expanded tokens\n");
		return (NULL);
	}
	if (build_expanded_content (xtkn, token, env, data) == 0)
	{
		printf("Error: There have been problems building the content of the expanded tokens\n");
		return (NULL);
	}
	return (xtkn);
}
