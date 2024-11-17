/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special_variables.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/17 02:50:00 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	manage_dollar_variable_between_quotes(t_general *data, t_token *token,
		t_xtkn *xtkn, int *i)
{
	account_quotes(token->content[*i], data);
	xtkn->content = strjoinchar(xtkn->content, '$');
	if (!xtkn->content)
		return (0);
	xtkn->content = strjoinchar(xtkn->content, token->content[*i]);
	if (!xtkn->content)
		return (0);
	(*i)++;
	return (1);
}

int	manage_miniquotes_after_dollar(t_general *data, t_token *token,
		t_xtkn *xtkn, int *i)
{
	account_quotes(token->content[*i], data);
	xtkn->content = strjoinchar(xtkn->content, token->content[*i]);
	if (!xtkn->content)
		return (0);
	(*i)++;
	return (1);
}

int	manage_quotes_after_dollar(t_general *data, t_token *token, t_xtkn *xtkn,
		int *i)
{
	account_quotes(token->content[*i], data);
	xtkn->content = strjoinchar(xtkn->content, token->content[*i]);
	if (!xtkn->content)
		return (0);
	(*i)++;
	return (1);
}

int	expand_digit_variable(t_general *data, t_token *token, t_xtkn *xtkn, int *i)
{
	if (data->qdata.miniquotes == 1)
	{
		xtkn->content = strjoinchar(xtkn->content, '$');
		if (!xtkn->content)
			return (0);
		xtkn->content = strjoinchar(xtkn->content, token->content[*i]);
		if (!xtkn->content)
			return (0);
	}
	else
	{
		if (token->content[*i] == '0')
			xtkn->content = adapted_strjoin(xtkn->content, "✌️ bash");
		else
			xtkn->content = adapted_strjoin(xtkn->content, "");
		if (!xtkn->content)
			return (0);
	}
	(*i)++;
	return (1);
}

int	expand_exit_status_variable(t_xtkn *xtkn, int exit_status, int *i)
{
	char	*exit_number;

	exit_number = ft_itoa(exit_status);
	if (!exit_number)
		return (0);
	xtkn->content = adapted_strjoin(xtkn->content, exit_number);
	if (!xtkn->content)
	{
		free(exit_number);
		return (0);
	}
	free(exit_number);
	(*i)++;
	printf ("exit status expandido: %s\n", xtkn->content);
	return (1);
}
