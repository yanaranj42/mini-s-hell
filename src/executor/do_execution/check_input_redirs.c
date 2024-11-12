/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 06:43:43 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	check_read_file(t_cmd *cmd, t_redir *redir)
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

void	check_input_redir(t_cmd *cmd, t_redir *redir)
{
	if (check_read_file(cmd, redir) == 0)
		exit(1);
	if (dup2(cmd->fd_in, 0) == -1)
	{
		perror_message(NULL, "Problem with dup2 of file std_input");
		exit(1);
	}
	close(cmd->fd_in);
}

void	check_heredoc_redir(t_cmd *cmd, t_redir *redir)
{
	cmd->fd_in = dup(redir->fd);
	close(redir->fd);
	if (dup2(cmd->fd_in, 0) == -1)
	{
		perror_message(NULL, "Problem with dup2 of heredoc std_input");
		exit(1);
	}
	close(cmd->fd_in);
}
