/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:21:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/19 22:58:43 by mfontser         ###   ########.fr       */
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
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			write (2, "Quit (core dumped)\n", 19);
			data->exit_status = 131;
		}
		else if (WTERMSIG(status) == SIGINT)
		{
			write (2, "\n", 1);
			data->exit_status = 130;
		}
	}
}
