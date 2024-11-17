/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/17 01:33:49 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	executor(t_general *data)
{
	//set_blocking_signals();
	if (preparations_for_the_executor(data) == 0)
		return (0);
	if (do_heredoc(data) == 0)
	{
		printf("Error: There have been problems doing the heredoc");
		return (0);
	}
	if (do_execution(data) == 0)
		return (0);
	father_status(data);
	return (1);
}
