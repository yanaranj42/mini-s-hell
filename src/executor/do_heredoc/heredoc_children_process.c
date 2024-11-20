/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_children_process.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 03:03:22 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 03:05:00 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	print_line_in_file(t_redir *redir, char *line, int *pipe_fd,
		t_general *data)
{
	char	*xline;

	xline = NULL;
	if (redir->heardoc_expansion == 1 && ft_strchr(line, '$'))
	{
		xline = expand_line(line, data);
		if (!xline)
			exit(1);
		write(pipe_fd[1], xline, ft_strlen(xline));
		write(pipe_fd[1], "\n", 1);
	}
	else
	{
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
	}
	if (xline)
	{
		free(xline);
		xline = NULL;
	}
}

int	check_limitter_word(char *line, int *pipe_fd, t_redir *redir)
{
	if (!line)
	{
		end_of_file_in_heredoc(redir->file_name);
		return (1);
	}
	if (ft_strncmp(line, redir->file_name, ft_strlen(redir->file_name)
			+ 1) == 0)
	{
		free(line);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		close(redir->fd);
		return (1);
	}
	return (0);
}

int	child_heredoc_process(t_general *data, int *pipe_fd, t_redir *redir)
{
	char	*line;

	init_heredoc_signals();
	while (1)
	{
		line = readline(YELLOW "> " END);
		if (check_limitter_word(line, pipe_fd, redir) == 1)
			exit(0);
		print_line_in_file(redir, line, pipe_fd, data);
		free(line);
	}
}
