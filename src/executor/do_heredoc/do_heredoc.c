/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/21 19:19:19 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	create_heredoc_pipe(t_general *data, int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		free_executor_process(data);
		return (0);
	}
	return (1);
}

int	manage_heredoc_stuff(t_general *data, int *pipe_fd, t_redir *redir)
{
	int	pid;

	pid = 0;
	if (create_heredoc_pipe(data, pipe_fd) == 0)
		return (0);
	redir->fd = dup(pipe_fd[0]);
	pid = fork();
	if (pid == -1)
	{
		free_heredoc_pipe(data, redir, pipe_fd);
		return (0);
	}
	if (pid == 0)
		child_heredoc_process(data, pipe_fd, redir);
	else
		init_ignore_signals();
	heredoc_father_status(data, &pid, pipe_fd);
	if (data->exit_status == 1)
	{
		free_executor_process(data);
		return (0);
	}
	return (1);
}

int	do_heredoc(t_general *data)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		pipe_fd[2];

	cmd = data->first_cmd;
	while (cmd)
	{
		redir = cmd->first_redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (manage_heredoc_stuff(data, pipe_fd, redir) == 0)
				{
					printf("Error: There have been problems with heredoc\n");
					return (0);
				}
			}
			if (data->exit_status == 130)
				return (free_control_c_in_heredoc(data), 0);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
