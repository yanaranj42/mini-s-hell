/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/17 04:07:54 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	executor(t_general *data)
{
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
