/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_xtkns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/21 12:28:47 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	change_non_printable_chars(t_xtkn *xtkn)
{
	int	i;

	i = 0;
	while (xtkn->content[i])
	{
		if (xtkn->content[i] == 30)
			xtkn->content[i] = '"';
		if (xtkn->content[i] == 31)
			xtkn->content[i] = '\'';
		i++;
	}
}

int	build_content_without_quotes(t_xtkn *xtkn, t_general *data, char **tmp)
{
	int	i;

	i = 0;
	while (xtkn->content[i])
	{
		account_quotes(xtkn->content[i], data);
		if (xtkn->content[i] == '"' && data->qdata.miniquotes == 0)
		{
			i++;
			continue ;
		}
		if (xtkn->content[i] == '\'' && data->qdata.quotes == 0)
		{
			i++;
			continue ;
		}
		*tmp = strjoinchar(*tmp, xtkn->content[i]);
		if (!*tmp)
			return (0);
		i++;
	}
	return (1);
}

int	remove_quotes(t_xtkn *xtkn, t_general *data)
{
	char	*tmp;

	init_quote_values(data);
	tmp = ft_strdup("");
	if (!tmp)
		return (0);
	if (build_content_without_quotes(xtkn, data, &tmp) == 0)
		return (0);
	free(xtkn->content);
	xtkn->content = ft_strdup(tmp);
	if (!xtkn->content)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

int	finish_xtkns(t_xtkn *first_xtkn, t_general *data)
{
	t_xtkn	*xtkn;

	xtkn = first_xtkn;
	while (xtkn)
	{
		if (remove_quotes(xtkn, data) == 0)
		{
			printf("Error: There have been problems finishing the expansion\n");
			return (0);
		}
		change_non_printable_chars(xtkn);
		xtkn = xtkn->next;
	}
	return (1);
}
