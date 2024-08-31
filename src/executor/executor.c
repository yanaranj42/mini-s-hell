/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/01 00:18:48 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	check_cmd(t_command *cmd, char **paths)
{
	split_cmd(cmd1);
	if (!cmd1->argv)
	{
		perror_message(NULL, "Malloc failure in take command 1 args");
		return (0);
	}
	if (!paths)
	{
		cmd1->path = check_cmd_absolut_path(cmd1->argv[0]);
		if (cmd1->path == NULL)
		{
			write (2, "Command not found: ", 19);
			write(2, cmd1->argv[0], ft_strlen(cmd1->argv[0]));
			write(2, "\n", 1);
			exit(127);
		}
	}
	else
		cmd1->path = check_cmd_access(paths, cmd1->argv[0]);
	return (1);
}


void	create_child(t_general *data, t_token *cmd1)
{

	//COMO SABER SI EL HIJO TIENE QUE PODER LEER O ESCRIBIR? Por el toquen que tiene a izquierda o derecha
	//COMO SABER SI TIENE UN ARCHIVO O SOLO UN COMANDO??

	//cada token corresponde a una cosa, no me voy a encontrar que en un toquen hay un archivo, un comando y una flag, o es archivo o es comando, y separados por separadores



	if (check_cmd(cmd, data->paths) == 0)
		exit(1);
	if (execve(cmd1->path, cmd1->argv, data->envp) == -1)
	{
		perror_message(NULL, "Regular command execve failed");
		exit(1);
	}
}


//pipex:
	// if (check_read_file(fdata) == 0)
	// 	exit(1);
	// if (check_cmd1(cmd1, data->paths) == 0)
	// 	exit(1);
	// if (dup2(fdata->infile_fd, 0) == -1)
	// {
	// 	perror_message(NULL, "Problem with dup2 of std_input in 1st command");
	// 	exit(1);
	// }
	// close(fdata->infile_fd);
	// if (dup2(data->pipe_fd[1], 1) == -1)
	// {
	// 	perror_message(NULL, "Problem with dup2 of std_output in 1st command");
	// 	exit(1);
	// }
	// close(data->pipe_fd[0]);
	// close(data->pipe_fd[1]);
	// if (execve(cmd1->path, cmd1->argv, data->envp) == -1)
	// {
	// 	perror_message(NULL, "Command 1 execve failed");
	// 	exit(1);
	// }


int count_commands(t_general *data)
{
	int n;
	t_token *tmp;

	n = 0;
	tmp = data->first_token;
	while (tmp)
	{
		if (tmp->type == NO_SEPARATOR)
			n++;
		tmp = tmp->next;
	}
	return (n);
}

void	get_children(t_general *data)
{
	//int		i;
	int 		n;
	pid_t		pid;
	t_command 	cmd;
	t_file		file;
	t_token 	tkn;

	printf ("# Get children:\n");
	//i = 0;
	n = count_commands(data);
	printf ("el valor de n es: %d\n", n);

	tkn = data->first_token;
	file = data->first_file; //FALTA INICIALIZAR Y VER EL CONJUNTO DE ESTAS TRES VARIABLES
	cmd = data->first_command;
	
	while (i < n)
	{
		pid = fork();
		if (pid == -1)
		{
			perror_message(NULL, "Fork");
			exit(1); //PORQUE 1???? Es el valor que solemos dar cuando fallan procesos internos tipo malloc, fork, dup2... 
			//PORQUE EXIT Y NO RETURN? QUE PASA CUANDO HAGO RETURN 0?
		}
		else
		{
			if (tkn->type != NO_SEPARATOR)
				tkn = tkn->next;
			if (tkn->type == NO_SEPARATOR)
			{
				if (tkn->back == NULL && (tkn->next == NULL || tkn->next->type == PIPE))
				{
					cmd->pid = pid; //aqui estoy metiendo informacion en el comando pero ya es dentro del hijo, cuando muera esa info se pierde? No la he modificado en el padre en teoria, no?
					cmd = cmd->next;
				}
				else 
				{
					file->pid = pid; //aqui estoy metiendo informacion en el comando pero ya es dentro del hijo, cuando muera esa info se pierde? No la he modificado en el padre en teoria, no?
					file = file->next;
				}
			}
			
		}
		if (pid == 0)
			create_child(data, tkn); //Entiendo que en el momento que se crea el fork se activa ese proceso, pero como sabe que lo que tiene que hacer es en ese proceso y no se mezclan?
		tkn = tkn->next;
		i++;
	}
}


int executor (t_general *data)
{
	printf (GREEN"\n******************* EXECUTOR *******************\n"END);
	if (get_all_paths(data->env_lst, data) == 0)
		return (0); // salimos del programa o al siguiente readline??????? Seria return para no machacar el perror, no?
	get_children(data);
	//get_children(data, data->first_command);
	// father_status(&data, &cmd1, &cmd2);
	// free_before_end(data.paths);
	return (1);
}

//CUANTOS COMANDOS HAY? -- EL MISMO QUE TOKENS DE TIPO NO_SEPARATOR
//


//los builtins que modifican las variables de entorno tienen que 
//hacerlo en el padre, porque sino no lo harian

//execute dicen que recibe doble puntero y que es mejor que los 
//builtins trabajen con doble puntero para que el executer ejecute como 
//tal o lo mande a builtins si hace falta, que pueda hacerlo con strncmp 
//sin tener que reconvertir variables 