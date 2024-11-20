/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:21:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 14:32:54 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	father_signal_status(t_general *data, int status)
{
	if (WTERMSIG(status) == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		data->exit_status = 131;
	}
	else if (WTERMSIG(status) == SIGINT)
	{
		write(2, "\n", 1);
		data->exit_status = 130;
	}
}

void	father_status(t_general *data)
{
	int		status;
	t_cmd	*tmp;

	tmp = data->first_cmd;
	status = 0;
	printf ("exit status 4 %d\n", data->exit_status);
	while (tmp)
	{
		status = 0;
		waitpid(tmp->pid, &status, 0);
		tmp = tmp->next;
	}
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	printf ("exit status 5 %d\n", data->exit_status);
	// else if (WIFSIGNALED(status))
	// 	father_signal_status(data, status);
}
