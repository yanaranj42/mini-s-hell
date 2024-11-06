/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_regular_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/06 16:14:34 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


char *identify_variable_to_expand (t_token *token, int *i)
{
	char *tmp;
	tmp = NULL;

	while (token->content[*i] && (ft_isalpha(token->content[*i]) == 1 || ft_isdigit(token->content[*i]) == 1 || token->content[*i] == '_'))
	{
		tmp = strjoinchar (tmp, token->content[*i]);
		if (!tmp)
			return (NULL);
		(*i)++;
	}
	printf ("  Contenido del xtkn después del $: |%s|\n", tmp);
	return (tmp);
}

int expand_regular_variable(t_token *token, t_xtkn	*xtkn, int *i, t_general *data)
{
	char *tmp;

	tmp = identify_variable_to_expand(token, i);
	if (!tmp)
		return (0);

	if (data->qdata.miniquotes == 1)
	{
		if (miniquotes_conversion (xtkn, tmp) == 0)
			return (0);
	}
	else if (data->qdata.quotes == 1)
	{
		if (quotes_conversion (xtkn, tmp, data->env_lst) == 0)
			return (0);
	}
	else
	{
		if (regular_conversion (token, xtkn, tmp, data->env_lst, i) == 0)
			return (0);
	}
	free(tmp);
	return (1);
}
