/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_xtkn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/29 00:57:09 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	enlarge_xtkns_list(t_xtkn *xtkn, t_general *data, int *i,
		char **splited_content, t_xtkn *new_xtkn)
{
	new_xtkn = create_xtoken();
	if (!new_xtkn)
	{
		printf("Error: There have been problems retokenizing\n");
		free_splited_content(splited_content);
		return (0);
	}
	new_xtkn->type = xtkn->type;
	new_xtkn->content = ft_strdup(splited_content[*i]);
	put_new_list_xtoken_node(data, new_xtkn);
	return (1);
}

int	retokenize_same_xtoken(t_xtkn *xtkn, char **splited_content)
{
	free(xtkn->content);
	xtkn->content = ft_strdup(splited_content[0]);
	if (!xtkn->content)
	{
		printf("Error: There have been problems retokenizing\n");
		free_splited_content(splited_content);
		return (0);
	}
	return (1);
}

int	adapt_xtkn_list(t_xtkn *xtkn, t_general *data, char **splited_content,
		t_xtkn *new_xtkn)
{
	int	i;

	if (retokenize_same_xtoken(xtkn, splited_content) == 0)
		return (0);
	i = 1;
	while (splited_content[i])
	{
		if (enlarge_xtkns_list(xtkn, data, &i, splited_content, new_xtkn) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	split_xtkn(t_xtkn *xtkn, t_general *data)
{
	char	**splited_content;
	int		i;
	t_xtkn	*new_xtkn;

	splited_content = ft_token_split(xtkn->content, ' ', data);
	if (!splited_content)
	{
		printf("Error: It's not possible to do the xtoken content split\n");
		return (0);
	}
	i = 0;
	while (splited_content[i])
		i++;
	new_xtkn = NULL;
	if (i > 1)
	{
		if (adapt_xtkn_list(xtkn, data, splited_content, new_xtkn) == 0)
			return (0);
	}
	free_splited_content(splited_content);
	return (1);
}
