/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_regular_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/19 23:23:18 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*identify_variable_to_expand(t_token *token, int *i)
{
	char	*tmp;

	tmp = NULL;
	while (token->content[*i] && (ft_isalpha(token->content[*i]) == 1
			|| ft_isdigit(token->content[*i]) == 1
			|| token->content[*i] == '_'))
	{
		tmp = strjoinchar(tmp, token->content[*i]);
		if (!tmp)
			return (NULL);
		(*i)++;
	}
	//printf("  Contenido del xtkn después del $: |%s|\n", tmp);
	return (tmp);
}

int	expand_regular_variable(t_token *token, t_xtkn *xtkn, int *i,
		t_general *data)
{
	t_convert	info;

	info.i = i;
	info.tmp = identify_variable_to_expand(token, i);
	if (!info.tmp)
		return (0);
	if (data->qdata.miniquotes == 1)
	{
		if (miniquotes_conversion(xtkn, info.tmp) == 0)
			return (0);
	}
	else if (data->qdata.quotes == 1)
	{
		if (quotes_conversion(xtkn, info.tmp, data->env_lst) == 0)
			return (0);
	}
	else
	{
		if (regular_conversion(&info, token, xtkn, data->env_lst) == 0)
			return (0);
	}
	free(info.tmp);
	return (1);
}
