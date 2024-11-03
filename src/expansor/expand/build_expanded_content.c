/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expanded_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/28 19:03:22 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int there_is_expansion_to_manage_2 (t_xtkn *xtkn, t_token *token, int * i, t_general *data)
{
	if (token->content[*i] && token->content[*i] == '"' && data->qdata.miniquotes == 0 && data->qdata.quotes == 0)
	{
		if (manage_quotes_after_dollar (data, token, xtkn, i) == 0)
			return (0);
	}
	else if (token->content[*i] && token->content[*i] == '\'' && data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
	{
		if (manage_miniquotes_after_dollar (data, token, xtkn, i) == 0)
			return (0);
	}
	else if (token->content[*i] && (token->content[*i] == '"' || token->content[*i] == '\''))
	{
		if (manage_dollar_variable_between_quotes (data, token, xtkn, i) == 0)
			return (0);
	}
	
	return (1);
}

int there_is_expansion_to_manage (t_xtkn *xtkn, t_token *token, t_env *env, int * i, t_general *data)
{
	if (token->content[*i] && (ft_isalpha(token->content[*i]) == 1 || token->content[*i] == '_'))
	{
		if (expand_regular_variable (token, xtkn, env, i, data) == 0)
			return (0);
	}
	else if (token->content[*i] && token->content[*i] == '?')
	{
		if (expand_exit_status_variable(xtkn, data->exit_status, i) == 0)
			return (0);
	}
	else if (token->content[*i] && ft_isdigit(token->content[*i]) == 1)
	{
		if (expand_digit_variable (data, token, xtkn, i) == 0)
			return (0);
	}
	else
	{
		if (there_is_expansion_to_manage_2 (xtkn, token, i, data) == 0)
			return (0);
	}
	return (1);	
}

int build_expanded_content (t_xtkn	*xtkn, t_token *token, t_env *env, t_general *data)
{
	int i;
	
	printf ("\n🟠 Toquen \n"); //BORRAR
	printf("\n# Expandir contenido del token |%s|\n", token->content);
	i = 0;
	xtkn->heardoc_expansion = 1;
	init_quote_values(data);
	while (token->content[i])
	{
		account_quotes (token->content[i], data);
		if (data->qdata.quotes == 1 || data->qdata.miniquotes == 1)
			xtkn->heardoc_expansion = 0;
		if(token->content[i] == '$')
		{
			i++;
			if (there_is_expansion_to_manage (xtkn, token, env, &i, data) == 0)
				return (0);
			continue ;
		}
		xtkn->content = strjoinchar (xtkn->content, token->content[i]);
		if (!xtkn->content)
			return (0);
		i++;
	}
	printf("  Hay que expandir en heredoc?: %d\n", xtkn->heardoc_expansion);
	return (1);
}
