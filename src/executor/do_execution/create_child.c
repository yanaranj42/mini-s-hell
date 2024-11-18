/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/18 23:09:44 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	check_redirs(t_cmd *cmd, t_redir *redir)
{
	if (redir->type == OUTPUT)
		check_output_redir(cmd, redir);
	else if (redir->type == APPEND)
		check_append_redir(cmd, redir);
	else if (redir->type == INPUT)
		check_input_redir(cmd, redir);
	else if (redir->type == HEREDOC)
		check_heredoc_redir(cmd, redir);
}

void	prepare_output_pipe(t_general *data)
{
	if (dup2(data->pipe_fd[1], 1) == -1)
	{
		perror_message(NULL, "Problem with dup2 of cmd std_output");
		exit(1);
	}
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
}

void	prepare_input_pipe(t_general *data)
{
	printf("dup2 input fd %d\n", data->next_cmd_input_fd);
	if (dup2(data->next_cmd_input_fd, 0) == -1)
	{
		perror_message(NULL, "Problem with dup2 of cmd std_input");
		exit(1);
	}
	close(data->next_cmd_input_fd);
}

int	create_child(t_general *data, t_cmd *cmd, int i, int n)
{
	t_redir	*redir;

	init_bloquing_signals();
	data->builtin = is_builtin(cmd);
	if (cmd->argv[0] && data->builtin == 0)
		check_cmd_path(cmd, data->paths);
	if (n > 1 && i != 0)
		prepare_input_pipe(data);
	if (n > 1 && i < (n - 1))
		prepare_output_pipe(data);
	redir = cmd->first_redir;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	while (redir)
	{
		check_redirs(cmd, redir);
		redir = redir->next;
	}
	execute_cmd(data, cmd);
	exit(0);
}
