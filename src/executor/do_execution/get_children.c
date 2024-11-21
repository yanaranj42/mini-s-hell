/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_children.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/21 13:20:18 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	init_new_process(t_general *data, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		free_executor_process(data);
		perror_message(NULL, "Fork");
		close(data->pipe_fd[1]);
		close(data->pipe_fd[0]);
		close(data->next_cmd_input_fd);
		return (0);
	}
	return (1);
}

void	create_pipe(t_general *data)
{
	if (pipe(data->pipe_fd) == -1)
	{
		perror_message(NULL, "Pipe");
		exit(1);
	}
}

int	duplicate_pipe_fd0(t_general *data)
{
	data->next_cmd_input_fd = dup(data->pipe_fd[0]);
	if (data->next_cmd_input_fd == -1)
	{
		free_executor_process(data);
		return (0);
	}
	close(data->pipe_fd[0]);
	return (1);
}

int	count_commands(t_general *data)//todo ok
{
	int		n;
	t_cmd	*tmp;

	n = 0;
	tmp = data->first_cmd;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}

int	get_children(t_general *data, int n, int i)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = data->first_cmd;
	init_fd_values(data);
	while (i < n)
	{
		redir = cmd->first_redir;
		if (data->pipe_fd[0] >= 0)
		{
			if (duplicate_pipe_fd0(data) == 0)
				return (0);
		}
		if (n > 1 && i < (n - 1))
			create_pipe(data);
		if (init_new_process(data, cmd) == 0)
			return (0);
		if (cmd->pid == 0)
			create_child(data, cmd, i, n);
		close_fds(data, redir);
		cmd = cmd->next;
		i++;
	}
	return (1);
}
