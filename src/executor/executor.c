/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/29 21:56:18 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	create_child(t_file *fdata, t_general *data, t_command *cmd1)
{

	//COMO SABER SI EL HIJO TIENE QUE PODER LEER O ESCRIBIR?
	//COMO SABER SI TIENE UN ARCHIVO O SOLO UN COMANDO??


//pipex:
	if (check_read_file(fdata) == 0)
		exit(1);
	if (check_cmd1(cmd1, data->paths) == 0)
		exit(1);
	if (dup2(fdata->infile_fd, 0) == -1)
	{
		perror_message(NULL, "Problem with dup2 of std_input in 1st command");
		exit(1);
	}
	close(fdata->infile_fd);
	if (dup2(data->pipe_fd[1], 1) == -1)
	{
		perror_message(NULL, "Problem with dup2 of std_output in 1st command");
		exit(1);
	}
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	if (execve(cmd1->path, cmd1->argv, data->envp) == -1)
	{
		perror_message(NULL, "Command 1 execve failed");
		exit(1);
	}
}

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

	printf ("# Get children:\n");
	//i = 0;
	n = count_commands(data);
	printf ("el valor de n es: %d\n", n);


	while (i < n)
	{
		pid = fork();
		if (pid == -1)
		{
			perror_message(NULL, "Fork");
			exit(1); //PORQUE 1????
		}
		else
		{
			cmd->pid = pid;
			cmd = cmd->next;
		}
		if (pid == 0)
			create_child(fdata, data, cmd1);
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