/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/19 22:57:43 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	print_line_in_file(t_redir *redir, char *line, int *pipe_fd,
		t_general *data)
{
	char *xline;

	xline = NULL;
	if (redir->heardoc_expansion == 1 && ft_strchr(line, '$'))
	{
		xline = expand_line(line, data); // REVISAR CASO DE QUE FALLE EL XLINE
		if (!xline)
			exit (1);
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
	free (line);
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

int	create_heredoc_pipe(t_general *data, int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		free_executor_process(data);
		return (0);
	}
	return (1);
}

void	heredoc_father_status(t_general *data, int *pid, int *pipe_fd)
{
	int		status;
	
	status = 0;
	waitpid(*pid, &status, 0);
	close (pipe_fd[0]);
	close (pipe_fd[1]);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write (2, "\n", 1);
			data->exit_status = 130;
		}
	}
}


int	manage_heredoc_stuff(t_general *data, int *pipe_fd, t_redir *redir)
{
	char	*line;
	int		pid;
	
	pid = 0;
	if (create_heredoc_pipe(data, pipe_fd) == 0)
		return (0);
	redir->fd = dup(pipe_fd[0]);
	pid = fork();
	if (pid == -1)
	{
		free_executor_process(data);
		perror_message(NULL, "Fork");
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		close(redir->fd);
		return (0);
	}
	if (pid == 0)
	{
		init_heredoc_signals();
		while (1)
		{
			line = readline(YELLOW "> " END);
			if (check_limitter_word(line, pipe_fd, redir) == 1)
				exit (0);
			print_line_in_file(redir, line, pipe_fd, data);
			// free(line);
		}
	}
	else
		init_ignore_signals ();
	heredoc_father_status(data, &pid, pipe_fd);
	if (data->exit_status == 1)
		return (0);
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






