/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniquotes_conversion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/17 17:45:16 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	miniquotes_conversion(t_xtkn *xtkn, char *tmp)
{
	xtkn->content = adapted_strjoin(xtkn->content, "$");
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
