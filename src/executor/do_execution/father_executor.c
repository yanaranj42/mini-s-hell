/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/06 02:59:18 by mfontser         ###   ########.fr       */
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


	//Permisos que indica el mode:
		//Propietario (usuario): Lectura y escritura. -> S_IRUSR | S_IWUSR
		//Grupo: Solo lectura. -> S_IRGRP
		//Otros usuarios: Solo lectura. -> S_IROTH;

	//Estos permisos son equivalentes a la máscara de permisos 0644 en formato octal

}

int check_father_output_redir (t_cmd *cmd, t_redir *redir, t_general *data)
{
	if (check_father_overwrite_file(cmd, redir) == 0)
	{
		free_executor_process (data);
		return (0);
	}
	if (dup2(cmd->fd_out, 1) == -1)
	{
		perror_message(NULL, "Problem with dup2 of file std_output");
		free_executor_process (data);
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

int check_father_append_redir (t_cmd *cmd, t_redir *redir, t_general *data)
{
	if (check_father_write_append_file(cmd, redir) == 0)
	{
		free_executor_process (data);
		return (0);
	}
	if (dup2(cmd->fd_out, 1) == -1)
	{
		perror_message(NULL, "Problem with dup2 of file std_output");
		free_executor_process (data);
		close(cmd->fd_out);
		return (0);
	}
	close(cmd->fd_out);
	return (1);
}



int	check_father_read_file(t_cmd *cmd, t_redir *redir)
{
	printf ("valor del fd: %d\n", cmd->fd_in);
	cmd->fd_in = open(redir->file_name, O_RDONLY);
	printf ("valor del fd: %d\n", cmd->fd_in);
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

int check_father_input_redir (t_cmd *cmd, t_redir *redir, t_general *data)
{
	if (check_father_read_file(cmd, redir) == 0)
	{
		free_executor_process (data);
		return (0);
	}
	if (dup2(cmd->fd_in, 0) == -1)
	{
		perror_message(NULL, "Problem with dup2 of file std_input");
		free_executor_process (data);
		close(cmd->fd_in);
		return (0);
	}
	close(cmd->fd_in);
	return (1);
}


int check_father_heredoc_redir (t_cmd *cmd, t_redir *redir, t_general *data)
{
	cmd->fd_in = dup (redir->fd);
	printf ("valor de redir->fd %d\n", redir->fd);
	close (redir->fd);
	if (dup2(cmd->fd_in, 0) == -1)
	{
		perror_message(NULL, "Problem with dup2 of heredoc std_input");
		free_executor_process (data);
		close(cmd->fd_in);
		return (0);
	}
	close(cmd->fd_in);
	return (1);
}

int check_father_redirs (t_general *data, t_cmd *first_cmd)
{
	t_redir *redir;

	redir = first_cmd->first_redir;
	while (redir)
	{ 
		printf ("entro\n");
		if (redir->type == OUTPUT) // >
		{
			if (check_father_output_redir (first_cmd, redir, data) == 0)
				return (0); 
		}
		else if (redir->type == APPEND) // >>
		{
			if (check_father_append_redir  (first_cmd, redir, data) == 0)
				return (0);
		}
		else if (redir->type == INPUT) // <
		{
			if (check_father_input_redir (first_cmd, redir, data) == 0)
				return (0);
		}
		else if (redir->type == HEREDOC) // <<
		{
			if (check_father_heredoc_redir (first_cmd, redir, data) == 0)
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}


//Estoy en el padre, por lo que si redirigo el stdoutput , todos los printfs y que haga desde ahi se redirigiran. En el hijo no pasa porque luego se muere, pero aqui se queda el cambio permanente.