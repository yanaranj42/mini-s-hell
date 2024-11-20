/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expanded_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 02:06:23 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	there_is_expansion_to_manage_2(t_xtkn *xtkn, t_token *token, int *i,
		t_general *data)
{
	if (token->content[*i] && token->content[*i] == '"'
		&& data->qdata.miniquotes == 0 && data->qdata.quotes == 0)
	{
		if (manage_quotes_after_dollar(data, token, xtkn, i) == 0)
			return (0);
	}
	else if (token->content[*i] && token->content[*i] == '\''
		&& data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
	{
		if (manage_miniquotes_after_dollar(data, token, xtkn, i) == 0)
			return (0);
	}
	else if (token->content[*i] && (token->content[*i] == '"'
			|| token->content[*i] == '\''))
	{
		if (manage_dollar_variable_between_quotes(data, token, xtkn, i) == 0)
			return (0);
	}
	return (1);
}

int	there_is_expansion_to_manage(t_xtkn *xtkn, t_token *token, int *i,
		t_general *data)
{
	if (token->content[*i] && (ft_isalpha(token->content[*i]) == 1
			|| token->content[*i] == '_'))
	{
		if (expand_regular_variable(token, xtkn, i, data) == 0)
			return (0);
	}
	else if (token->content[*i] && token->content[*i] == '?')
	{
		if (expand_exit_status_variable(xtkn, data->exit_status, i) == 0)
			return (0);
	}
	else if (token->content[*i] && ft_isdigit(token->content[*i]) == 1)
	{
		if (expand_digit_variable(data, token, xtkn, i) == 0)
			return (0);
	}
	else
	{
		if (there_is_expansion_to_manage_2(xtkn, token, i, data) == 0)
			return (0);
	}
	return (1);
}

int	build_expanded_content(t_xtkn *xtkn, t_token *token, t_general *data)
{
	int	i;

	i = 0;
	xtkn->heardoc_expansion = 1;
	init_quote_values(data);
	while (token->content[i])
	{
		account_quotes(token->content[i], data);
		if (data->qdata.quotes == 1 || data->qdata.miniquotes == 1)
			xtkn->heardoc_expansion = 0;
		if (token->content[i] == '$')
		{
			i++;
			if (there_is_expansion_to_manage(xtkn, token, &i, data) == 0)
				return (0);
			continue ;
		}
		xtkn->content = strjoinchar(xtkn->content, token->content[i]);
		if (!xtkn->content)
			return (0);
		i++;
	}
	return (1);
}
