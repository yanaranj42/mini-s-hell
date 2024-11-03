/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/28 21:16:47 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int manage_quotes_variable (t_xtkn	*xtkn, char *tmp, t_env *env)
{
	if (check_expansor_variable_exists (tmp, env) == 0)
	{
		xtkn->content = adapted_strjoin(xtkn->content, "");
		if (!xtkn->content)
		{
			free(tmp);
			return (0);
		}
	}
	else
	{
		if (change_expansor_variable(xtkn,tmp, env) == 0)
		{
			free(tmp);
			return (0);
		}
	}
	return (1);		
}

int build_heredoc_delimiter (t_xtkn	*xtkn, char *tmp)
{
	xtkn->content = strjoinchar (xtkn->content, '$');
	if (!xtkn->content)
	{
		free(tmp);
		return (0);
	}
	xtkn->content = adapted_strjoin(xtkn->content, tmp);
	if (!xtkn->content)
	{
		free(tmp);
		return (0);
	}
	return (1);
}

int quotes_conversion (t_xtkn	*xtkn, char *tmp, t_env *env)
{
	if (xtkn->back && xtkn->back->type == HEREDOC) // Si antes tiene un heredoc quiere decir que es un limitador y no se tiene que expandir
	{
		if (build_heredoc_delimiter (xtkn, tmp) == 0)
			return (0);
	}
	else
	{
		if (manage_quotes_variable (xtkn,tmp, env) == 0)
			return (0);
	}
	return (1);	
}