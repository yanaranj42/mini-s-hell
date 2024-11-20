/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_father_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 03:04:33 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 03:04:48 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	heredoc_father_status(t_general *data, int *pid, int *pipe_fd)
{
	int	status;

	status = 0;
	waitpid(*pid, &status, 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(2, "\n", 1);
			data->exit_status = 130;
		}
	}
}
