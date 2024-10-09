/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:21:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/22 19:41:42 by mfontser         ###   ########.fr       */
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
	status = 0; // acostumbrarme a inicializar las variables siempre, porque aqui si no entro en el while el status se queda sin asignacion
	while (tmp) // importante poner wait por cada comando
	{
		status = 0;// status acumula la basura del wait anterior. Al ponerlo en 0 reseteo la plantilla. El waitpid pondra los bits en 1 que correspondan en el status.
		waitpid(tmp->pid, &status, 0); //coge el valor de retorno del exit del hijo (unica forma de comunicarme entre padre e hijo)
		tmp = tmp->next;
	}
	// waitpid(last_pid, &status, 0);
	// while (wait());
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
}
