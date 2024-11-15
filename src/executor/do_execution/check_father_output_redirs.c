/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_father_output_redirs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/09 20:52:15 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	check_father_overwrite_file(t_cmd *cmd, t_redir *redir)
{
	int		flags;
	mode_t	mode;

	flags = O_CREAT | O_TRUNC | O_WRONLY;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (ft_strchr(redir->file_name, '$'))
	{
		ambiguous_redirect(redir->file_name);
		return (0);
	}
	cmd->fd_out = open(redir->file_name, flags, mode);
	if (cmd->fd_out < 0)
	{
		perror_message(redir->file_name, "");
		return (0);
	}
	return (1);
}

int	check_father_output_redir(t_cmd *cmd, t_redir *redir, t_general *data)
{
	if (check_father_overwrite_file(cmd, redir) == 0)
	{
		free_executor_process(data);
		return (0);
	}
	if (dup2(cmd->fd_out, 1) == -1)
	{
		perror_message(NULL, "Problem with dup2 of file std_output");
		free_executor_process(data);
		close(cmd->fd_out);
		return (0);
	}
	close(cmd->fd_out);
	return (1);
}

int	check_father_write_append_file(t_cmd *cmd, t_redir *redir)
{
	int		flags;
	mode_t	mode;

	flags = O_CREAT | O_APPEND | O_WRONLY;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (ft_strchr(redir->file_name, '$'))
	{
		ambiguous_redirect(redir->file_name);
		return (0);
	}
	cmd->fd_out = open(redir->file_name, flags, mode);
	if (cmd->fd_out < 0)
	{
		perror_message(redir->file_name, "");
		return (0);
	}
	return (1);
}

int	check_father_append_redir(t_cmd *cmd, t_redir *redir, t_general *data)
{
	if (check_father_write_append_file(cmd, redir) == 0)
	{
		free_executor_process(data);
		return (0);
	}
	if (dup2(cmd->fd_out, 1) == -1)
	{
		perror_message(NULL, "Problem with dup2 of file std_output");
		free_executor_process(data);
		close(cmd->fd_out);
		return (0);
	}
	close(cmd->fd_out);
	return (1);
}