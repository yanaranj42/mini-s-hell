/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/19 22:49:13 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"


void close_heredoc_fds (t_general *data)
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

int	executor(t_general *data)
{
	if (preparations_for_the_executor(data) == 0)
		return (0);
	if (do_heredoc(data) == 0)
	{
		printf("Error: There have been problems doing the heredoc");
		return (0);
	}
	if (data->exit_status == 130)
	{
		free_matrix_env(data);
		free_data_paths(data);
		close_heredoc_fds (data);
		free_cmd(data);
		return (0);
	}
	if (do_execution(data) == 0)
		return (0);
	father_status(data);
	return (1);
}
