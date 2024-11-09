/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/06 06:36:36 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


void create_pipe(t_general *data)
{
	if (pipe(data->pipe_fd) == -1)
	{
		perror_message(NULL, "Pipe");
		exit (1);
	}
}


void prepare_output_pipe(t_general *data)
{
	if (dup2(data->pipe_fd[1], 1) == -1)
	{
		perror_message(NULL, "Problem with dup2 of cmd std_output");
		exit(1);
	}
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
}

void prepare_input_pipe(t_general *data)
{
	printf("dup2 input fd %d\n", data->next_cmd_input_fd);
	if (dup2(data->next_cmd_input_fd, 0) == -1)
	{
		perror_message(NULL, "Problem with dup2 of cmd std_input");
		exit(1);
	}
	close(data->next_cmd_input_fd);
}

int	check_overwrite_file(t_cmd *cmd, t_redir *redir)
{
	int		flags;
	mode_t	mode;

	flags = O_CREAT | O_TRUNC | O_WRONLY;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (ft_strchr (redir->file_name, '$'))
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

void check_output_redir (t_cmd *cmd, t_redir *redir)
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
	if (ft_strchr (redir->file_name, '$'))
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

void check_append_redir (t_cmd *cmd, t_redir *redir)
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


int	check_read_file(t_cmd *cmd, t_redir *redir)
{
	cmd->fd_in = open(redir->file_name, O_RDONLY);
	if (cmd->fd_out < 0 && ft_strchr (redir->file_name, '$'))
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

void check_input_redir (t_cmd *cmd, t_redir *redir)
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


void check_heredoc_redir (t_cmd *cmd, t_redir *redir)
{
	cmd->fd_in = dup (redir->fd);
	printf ("valor de redir->fd %d\n", redir->fd);
	close (redir->fd);
	if (dup2(cmd->fd_in, 0) == -1)
	{
		perror_message(NULL, "Problem with dup2 of heredoc std_input");
		exit(1);
	}
	close(cmd->fd_in);
}

void check_redirs (t_cmd *cmd, t_redir *redir)
{
	if (redir->type == OUTPUT) // >
		check_output_redir (cmd, redir);
	else if (redir->type == APPEND) // >>
		check_append_redir  (cmd, redir);
	else if (redir->type == INPUT) // <
		check_input_redir (cmd, redir);
	else if (redir->type == HEREDOC) // <<
		check_heredoc_redir (cmd, redir);
}


void execute_cmd (t_general *data, t_cmd *cmd)
{
	data->builtin = is_builtin(cmd);
	if (cmd->argv[0] && data->builtin == 0)
	{
		if (execve(cmd->path, cmd->argv, data->env_matrix) == -1)
		{
			perror_message (NULL, "Execve failed");
			exit(1);
		}
	}
	else if (cmd->argv[0] && data->builtin != 0)
		execute_builtin(data, cmd);
}

int	create_child(t_general *data, t_cmd *cmd, int i, int n)
{
	t_redir *redir;
	
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
		check_redirs (cmd, redir);
		redir = redir->next;
	}
	execute_cmd (data, cmd);
	exit (0);
}

int count_commands(t_general *data)
{
	int n;
	t_cmd *tmp;

	n = 0;
	tmp = data->first_cmd;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}


int	check_executor_type (t_general *data)
{
	t_cmd *cmd;

	cmd = data->first_cmd;
	data->builtin = is_builtin(cmd);
	if (cmd->argv[0] && data->builtin != 0 && !cmd->next)
		return (1);
	return (0);
}

int duplicate_pipe_fd0 (t_general *data)
{
	data->next_cmd_input_fd = dup(data->pipe_fd [0]);
	if (data->next_cmd_input_fd == -1)
	{
		free_executor_process (data);
		return (0);
	}
	close(data->pipe_fd[0]);
	return (1);
}

int init_new_process (t_general *data, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		free_executor_process (data);
		perror_message(NULL, "Fork");
		close(data->pipe_fd[1]);
		close(data->pipe_fd[0]);
		close(data->next_cmd_input_fd);
		return (0); 
	}
	return (1);
}

void close_fds (t_general *data, t_redir *redir)
{
	close(data->pipe_fd[1]);
	close(data->next_cmd_input_fd);
	while (redir)
	{
		if (redir->type == HEREDOC)
			close(redir->fd);
		redir = redir->next;
	}
}

int	get_children(t_general *data)
{
	int			i;
	int 		n;
	t_cmd 		*cmd;
	t_redir *redir;

	i = 0;
	n = count_commands(data);
	cmd = data->first_cmd;
	data->pipe_fd[0] = -1; 
	data->pipe_fd[1] = -1; 
	data->next_cmd_input_fd = -1;
	while (i < n)
	{
		redir = cmd->first_redir;
		if (data->pipe_fd[0] >= 0)
		{
			if (duplicate_pipe_fd0 (data) == 0)
				return (0);	
		}		
		if (n > 1 && i < (n - 1))
			create_pipe(data);
		if (init_new_process (data, cmd) == 0)
			return (0);
		if (cmd->pid == 0) 
			create_child(data, cmd, i, n);
		close_fds (data, redir);
		cmd = cmd->next;
		i++;
	}
	return (1);
}






int builtin_execution_only (t_general *data)
{
	int copy_stdin;
	int copy_stdout;

	copy_stdin = dup(STDIN_FILENO);
	copy_stdout = dup(STDOUT_FILENO);
	if (check_father_redirs(data, data->first_cmd) == 0)
	 	return (0);
	execute_builtin(data, data->first_cmd);
	if (dup2 (copy_stdin, 0) == -1)
	{
		free_builtin_execution_only (data, &copy_stdin, &copy_stdout, "Problem with dup2 of builtin std_input");
		exit (1);	
	}
	if (dup2 (copy_stdout, 1) == -1)
	{
		free_builtin_execution_only (data, &copy_stdin, &copy_stdout, "Problem with dup2 of builtin std_output");
		exit (1);
	}
	close (copy_stdin);
	close (copy_stdout);
	return (1);
}

int do_execution (t_general *data)
{
	if (check_executor_type (data) == 1)
	{
		if (builtin_execution_only (data) == 0)
			return (0);
	}
	
	else if (get_children(data) == 0)
		return (0);
	return (1);
}

int preparations_for_the_executor (t_general *data)
{
	if (get_matrix_env (data, data->env_lst) == 0)
	{
		printf("Failure in matrix enviroment creation");
		data->exit_status = 1;
		return (0); 
	}
	if (get_all_paths(data->env_lst, data) == 0)
		return (0);    
	if (get_command(data, data->first_xtkn) == 0)
	{
		printf("Error: There have been problems creating commands");
		return (0); 
	}
	free_xtkns_list(data);
	return (1);
}



int executor (t_general *data)
{
	if (preparations_for_the_executor (data) == 0)
		return (0);    
	if (do_heredoc(data) == 0)
	{
		printf("Error: There have been problems doing the heredoc");
		return (0);
	}
	if (do_execution (data) == 0)
		return (0);    
	
	father_status(data);
	return (1);
}
