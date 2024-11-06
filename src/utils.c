/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:50:06 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/06 05:52:44 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void account_quotes (char c, t_general *data)
{
	if (c == '"' && data->qdata.miniquotes == 0)
		{
			if (data->qdata.quotes == 0)
				data->qdata.quotes = 1;
			else if(data->qdata.quotes == 1)
				data->qdata.quotes = 0;
		}
	else if (c == '\'' && data->qdata.quotes == 0)
		{
			if (data->qdata.miniquotes == 0)
				data->qdata.miniquotes = 1;
			else if(data->qdata.miniquotes == 1)
				data->qdata.miniquotes  = 0;
		}
}
