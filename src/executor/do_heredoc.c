/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/04 22:19:03 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int create_heredoc_pipe(t_general *data, int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		free_heredoc_process (data);
		return (0);
	}
	return (1);
}

int check_limitter_word (char 		*line, int *pipe_fd, t_redir 	*redir)
{
	if (ft_strncmp(line, redir->file_name, ft_strlen(redir->file_name) + 1) == 0)
	{
		free(line);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		return (1);
	}
	return (0);
}

void print_line_in_file(t_redir 	*redir, char 		*line, int *pipe_fd, t_general *data)
{
	printf ("expansion heredoc %d\n", redir->heardoc_expansion);
	if (redir->heardoc_expansion == 1 && ft_strchr(line, '$')) // Hay que expandir el contenido de la linea
		line = expand_line (line, data);
	write(pipe_fd[1], line, ft_strlen(line));
	printf ("lo que hay en la linea es: %s\n", line);
	write(pipe_fd[1], "\n", 1);
}


int manage_heredoc_stuff (t_general *data,  int *pipe_fd, t_redir 	*redir)
{
	char 		*line;
	if (create_heredoc_pipe(data, pipe_fd) == 0)
		return (0);
	redir->fd = dup (pipe_fd[0]);
	while (1) // esto es lo que deja abierto el proceso para poder escribir eternamente, hasta que no escriba el limitador el programa no se seguira ejecutando
		{
		// leo de terminal
		line =  readline(YELLOW"> "END);
		// si la linea leida de terminal es = al limitador, cierro el fd de escritura y paro el bucle de lectura
		printf ("valor de fd[0]: %d\n",  pipe_fd [0]);
		printf ("valor de fd[1]: %d\n",  pipe_fd [1]);
		printf ("valor de redir->fd %d\n", redir->fd);
		if (check_limitter_word (line,  pipe_fd, redir) == 1)
			break;					
		//escribo la linea en el archivo pipe.txt, por el fd de escritura
		print_line_in_file(redir, line,  pipe_fd, data);
		free (line);
	}
	return (1);
}

int do_heredoc(t_general *data)
{
	t_cmd 		*cmd;
	t_redir 	*redir;
	int			pipe_fd[2];
	

	cmd = data->first_cmd;
	while (cmd)
	{
		redir = cmd->first_redir;		
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (manage_heredoc_stuff (data, pipe_fd, redir) == 0)
					return (0);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	printf ("   valor de fd[0]: %d\n",  pipe_fd [0]);
		printf ("   valor de fd[1]: %d\n",  pipe_fd [1]);
	return (1);
}