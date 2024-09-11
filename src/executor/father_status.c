/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:21:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/10 16:08:21 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	father_status(t_general *data)
{
	int	status;
	t_token *tmp;

	tmp = data->first_token;

	// close(data->pipe_fd[0]);
	// close(data->pipe_fd[1]);
	while (tmp->type != CMD)
		tmp = tmp->next;
	waitpid(tmp->pid, &status, 0); //coge el valor de retorno del exit del hijo (unica forma de comunicarme entre padre e hijo)
	// waitpid(cmd2->pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
}
