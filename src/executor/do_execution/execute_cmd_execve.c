/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_execve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/09 22:32:49 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	close_fds(t_general *data, t_redir *redir)
{
	close(data->pipe_fd[1]);
	close(data->next_cmd_input_fd);
	while (redir)
	{
		if (redir->type == HEREDOC)
			close(redir->fd);
		redir = redir->next;
	}
}

void	execute_cmd(t_general *data, t_cmd *cmd)
{
	data->builtin = is_builtin(cmd);
	if (cmd->argv[0] && data->builtin == 0)
	{
		if (execve(cmd->path, cmd->argv, data->env_matrix) == -1)
		{
			perror_message(NULL, "Execve failed");
			exit(1);
		}
	}
	else if (cmd->argv[0] && data->builtin != 0)
		execute_builtin(data, cmd);
}
