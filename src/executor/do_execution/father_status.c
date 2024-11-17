/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:21:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/09 22:36:18 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	father_status(t_general *data)
{
	int		status;
	t_cmd	*tmp;

	tmp = data->first_cmd;
	status = 0;
	while (tmp)
	{
		status = 0;
		waitpid(tmp->pid, &status, 0);
		tmp = tmp->next;
	}
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
}
