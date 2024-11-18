/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/18 13:30:29 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	print_line_in_file(t_redir *redir, char *line, int *pipe_fd,
		t_general *data)
{
	if (redir->heardoc_expansion == 1 && ft_strchr(line, '$'))
		line = expand_line(line, data);
	write(pipe_fd[1], line, ft_strlen(line));
	write(pipe_fd[1], "\n", 1);
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
		return (1);
	}
	return (0);
}

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
	char	*line;

	if (create_heredoc_pipe(data, pipe_fd) == 0)
		return (0);
	redir->fd = dup(pipe_fd[0]);
	signal(SIGINT, handle_sig_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (g_error == 42)
			break ;
		line = readline(YELLOW "> " END); //hija mata proceso al recibir signal
		if (check_limitter_word(line, pipe_fd, redir) == 1)
			break ;
		print_line_in_file(redir, line, pipe_fd, data);
		free(line);
	}
	set_sig_default();//set signals back
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
					return (0);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
