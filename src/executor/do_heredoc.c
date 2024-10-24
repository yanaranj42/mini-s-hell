/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/24 20:01:56 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int do_heredoc(t_general *data)
{
	t_cmd 		*cmd;
	t_redir 	*redir;
	int			pipe_fd[2];
	char 		*line;

	cmd = data->first_cmd;
	
	while (cmd)
	{
		redir = cmd->first_redir;		
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (pipe(pipe_fd) == -1)
				{
					free_matrix_env(data);
					free_data_paths (data);
					free_cmd(data);
					data->exit_status = 1;
					return (0);
				}
				while (1) // esto es lo que deja abierto el proceso para poder escribir eternamente, hasta que no escriba el limitador el programa no se seguira ejecutando
 				{
					// leo de terminal
					line =  readline(YELLOW"> "END);
					// si la linea leida de terminal es = al limitador, cierro el fd de escritura y paro el bucle de lectura
					if (ft_strncmp(line, redir->file_name, ft_strlen(redir->file_name) + 1) == 0)
					{
						free(line);
						close(pipe_fd[1]);
						break ;
					}
					//escribo la linea en el archivo pipe.txt, por el fd de escritura
					printf ("expansion heredoc %d\n", redir->heardoc_expansion);
					if (redir->heardoc_expansion == 1 && ft_strchr(line, '$')) // Hay que expandir el contenido de la linea
						line = expand_line (line, data->env_lst, data->exit_status);
					write(pipe_fd[1], line, ft_strlen(line));
					write(pipe_fd[1], "\n", 1);
					redir->fd = dup (pipe_fd[0]);
					free (line);
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}