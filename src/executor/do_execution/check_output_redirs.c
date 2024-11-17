/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_output_redirs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/09 21:30:29 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	check_overwrite_file(t_cmd *cmd, t_redir *redir)
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

void	check_output_redir(t_cmd *cmd, t_redir *redir)
{
	if (check_overwrite_file(cmd, redir) == 0)
		exit(1);
	if (dup2(cmd->fd_out, 1) == -1)
	{
		perror_message(NULL, "Problem with dup2 of file std_output");
		exit(1);
	}
	close(cmd->fd_out);
}

int	check_write_append_file(t_cmd *cmd, t_redir *redir)
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

void	check_append_redir(t_cmd *cmd, t_redir *redir)
{
	if (check_write_append_file(cmd, redir) == 0)
		exit(1);
	if (dup2(cmd->fd_out, 1) == -1)
	{
		perror_message(NULL, "Problem with dup2 of file std_output");
		exit(1);
	}
	close(cmd->fd_out);
}
