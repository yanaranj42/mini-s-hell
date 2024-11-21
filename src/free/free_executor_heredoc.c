/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_executor_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 02:25:23 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 02:34:53 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	close_heredoc_fds(t_general *data)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = data->first_cmd;
	while (cmd)
	{
		redir = cmd->first_redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
				close(redir->fd);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	free_control_c_in_heredoc(t_general *data)
{
	free_matrix_env(data);
	free_data_paths(data);
	close_heredoc_fds(data);
	free_cmd(data);
}

void	free_heredoc_pipe(t_general *data, t_redir *redir, int *pipe_fd)
{
	free_executor_process(data);
	perror_message(NULL, "Fork");
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	close(redir->fd);
}
