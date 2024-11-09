/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmd_argvs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/04 03:13:26 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


int count_cmd_argvs (t_xtkn **count_xtkn)
{
	int  	count;

	count = 0;
	while (*count_xtkn && (*count_xtkn)->type != PIPE)
	{
		if ((*count_xtkn)->type == CMD_ARGV)
			count++;
		*count_xtkn = (*count_xtkn)->next;
	}
	return (count);
}
