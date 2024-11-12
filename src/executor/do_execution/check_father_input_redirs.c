/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_father_input_redirs.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 06:55:38 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	check_father_read_file(t_cmd *cmd, t_redir *redir)
{
	cmd->fd_in = open(redir->file_name, O_RDONLY);
	if (cmd->fd_out < 0 && ft_strchr(redir->file_name, '$'))
	{
		ambiguous_redirect(redir->file_name);
		return (0);
	}
	if (cmd->fd_in < 0)
	{
		perror_message(redir->file_name, "");
		return (0);
	}
	return (1);
}

int	check_father_input_redir(t_cmd *cmd, t_redir *redir, t_general *data)
{
	if (check_father_read_file(cmd, redir) == 0)
	{
		free_executor_process(data);
		return (0);
	}
	if (dup2(cmd->fd_in, 0) == -1)
	{
		perror_message(NULL, "Problem with dup2 of file std_input");
		free_executor_process(data);
		close(cmd->fd_in);
		return (0);
	}
	close(cmd->fd_in);
	return (1);
}

int	check_father_heredoc_redir(t_cmd *cmd, t_redir *redir, t_general *data)
{
	cmd->fd_in = dup(redir->fd);
	close(redir->fd);
	if (dup2(cmd->fd_in, 0) == -1)
	{
		perror_message(NULL, "Problem with dup2 of heredoc std_input");
		free_executor_process(data);
		close(cmd->fd_in);
		return (0);
	}
	close(cmd->fd_in);
	return (1);
}
