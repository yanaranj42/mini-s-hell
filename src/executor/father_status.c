/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:21:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/15 20:58:41 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	father_status(t_general *data)
{
	int	status;
	t_cmd *tmp;

	tmp = data->first_cmd;

	// close(data->pipe_fd[0]);
	// close(data->pipe_fd[1]);
	while (tmp) // importante poner wait por cada comando
	{
		status = 0;// acumula la basura del wait anterior. Al ponerlo en 0 reseteo la plantilla. El waitpid pondra los bits en 1 que correspondan en el status.
		waitpid(tmp->pid, &status, 0); //coge el valor de retorno del exit del hijo (unica forma de comunicarme entre padre e hijo)
		tmp = tmp->next;
	}
	// waitpid(CMD_ARGV2->pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
}
