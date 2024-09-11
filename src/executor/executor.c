/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/11 21:12:19 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Planteamiento evolucion executor:
	// Ejecutar comando unico
	// Ejecutar varios comandos, simplemente saltadome los separdos
	// Ejectuar los pipes
	// Hacer redirecciones a la derecha > >>
	// Hacer redicrecciones a la izquierda < <<


// En el caso de que el token sea < infile cat, dejar que se ejecute el < infile, y luego reconvertir el token a cat (lo machaco)



// if (dup2(fdata->infile_fd, 0) == -1)
// 	{
// 		perror_message(NULL, "Problem with dup2 of std_input in 1st command");
// 		exit(1);
// 	}
// 	close(fdata->infile_fd);
// 	if (dup2(data->pipe_fd[1], 1) == -1)
// 	{
// 		perror_message(NULL, "Problem with dup2 of std_output in 1st command");
// 		exit(1);
// 	}
// 	close(data->pipe_fd[0]);
// 	close(data->pipe_fd[1]);



// if (dup2(fdata->outfile_fd, 1) == -1)
// 	{
// 		perror_message(NULL, "Problem with dup2 of std_output in 2nd command");
// 		exit(1);
// 	}
// 	close(fdata->outfile_fd);
// 	if (dup2(data->pipe_fd[0], 0) == -1)
// 	{
// 		perror_message(NULL, "Problem with dup2 of std_input in 2nd command");
// 		exit(1);
// 	}
// 	close(data->pipe_fd[0]);
// 	close(data->pipe_fd[1]);



// //FUNCION TEMPORAL PARA DEBUGAR. LUEGO BORRAR
// void debug_token(t_token *token, int num)
// {
// 	int i;
// 	char *type[] = {"null", "pipe", "stdin_redirection", "stdin_double_redirection", "stdout_redirection", "stdout_double_redirection", "WORD"};

// 	i = 0;
// 	printf("\n  >> Contenido del token %d:\n", num);
// 	printf("     argc = %d\n", token->argc);
// 	while (token->argv[i])
// 	{
// 		printf("     argv[%d] = |%s|\n", i, token->argv[i]);
// 		i++;
// 	}
// 	printf("     tipo de token: %d (%s)\n", token->type, type[token->type]);
// 	printf("     token actual: %p\n", token);
// 	printf("     next apunta a %p\n", token->next);
// 	printf("     back apunta a %p\n\n", token->back);
// }






void create_pipe(t_general *data)
{
	if (pipe(data->pipe_fd) == -1)
	{
		perror_message(NULL, "Pipe");
		exit (1);
	}
}


void prepare_1st_command_pipe(t_general *data)
{
	//De momento solo pongo comandos, como no hay archivos de los que leer no tengo que cambiar el stdin, leera de la linea de comandos y se guardara el resultado
	if (dup2(data->pipe_fd[1], 1) == -1)
	{
		perror_message(NULL, "Problem with dup2 of std_output");
		exit(1);
	}
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
}

void prepare_2nd_command_pipe(t_general *data)
{
	if (dup2(data->pipe_fd[0], 0) == -1)
	{
		perror_message(NULL, "Problem with dup2 of std_input in 2nd command");
		exit(1);
	}
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
}

int	create_child(t_general *data, t_token *tkn)
{

	//COMO SABER SI EL HIJO TIENE QUE PODER LEER O ESCRIBIR? Por el toquen que tiene a izquierda o derecha
	//COMO SABER SI TIENE UN ARCHIVO O SOLO UN COMANDO??

	//cada token corresponde a una cosa, no me voy a encontrar que en un toquen hay un archivo, un comando y una flag, o es archivo o es comando, y separados por separadores

	
	write(1, PURPLE, ft_strlen(PURPLE)); // BORRAR
	write(1, "\nSOY UN HIJO\n", 13); // BORRAR
	write(1, "\n# Checkear comandos:\n", 22); // BORRAR
	write(2, END, ft_strlen(END)); // BORRAR
	//si no hago esperar al padre mientras el hijo hace cosas, el padre sigue y me aparece el siguiente readline en medio, por eso cuando el hijo acaba no me aparece el prompt, porque ya estoy ahi
	check_cmd(tkn, data->paths);
	printf ("\n");
	printf ("   >>> Token path antes del execve: %s\n", tkn->path);
	if (tkn->next && tkn->next->type == PIPE)
	{
		
		prepare_1st_command_pipe(data); // redirecciono el output del comando hacia el fd 1 de la pipe
	}
	if (tkn->back->type == PIPE)
		prepare_2nd_command_pipe(data); // le digo que el infile del comando sea el fd 0 de la pipe 

	printf(PURPLE"\n# Excecve:\n"END);
	printf ("\n");
	if (execve(tkn->path, tkn->argv, data->env_matrix) == -1) // si el execve no puede ejecutar el comando con la info que le hemos dado (ej: ls sin ningun path), nos da -1. El execve le dara un valor que recogera el padre para el exit status.
	{
		perror_message(NULL, "Execve failed");
		exit(1);
	}
	return (1);
}

//!!!REVISAR:
// EL PERROR, LO UNICO QUE NO GESTIONA ES EL COMMAND NOT FOUND, HAY QUE HARDCODEARLO. SI NO ENCUENTRA EL COMANDO EN EL PATH, COMMAND NOT FOUND
// AHORA ESTOY DICIENDO QUE SI NO ENCUENTRA EL PATH O NO EXISTE, QUE EL PATH ES EL PROPIO COMANDO Y LO INTENTE IGUAL, Y ME DICE ARCHIVO NO ENCONTRADO, PERO ESO ESTA MAL.
// ESO TENGO QUE HACERLO ASI SOLO SI ME PASAN EL COMANDO CON LA RUTA ABSOLUTA, SI HAY UNA / EN EL COMANDO (QUE SIGNIFICA QUE ESTOY PASANDO UNA RUTA ABSOLUTA, O INTENTANDOLO). EN ESE MOMENTO SI QUE INDEPENDIENTEMENTE DE QUE NO LO ENCUENTRE SE LO TENGO QUE PASAR AL PERROR PARA QUE ME PASE EL ERROR DE FILE NOT FOUND


//El execve solo ejecuta comandos de los que tiene el path. Aunque haya path, comandos del sistema como cd, export o unset, no los encuentra como el resto, por lo tanto tampoco los puede ejecutar.


//Quan entro un comando al sistema primer mira si esta la ruta que li passo, ja sigui absoluta o relativa. si li passo el comando a secas, la ruta relativa es ./comando, busca el comando a la carpeta que jo estic
//quan jo li entro a secas un comando la terminal enten que es una ruta relativa a la propia carpeta. En el cas de que no ho trobi, ho busca en els diferents del enviroment i va probant desquerra a dreta fins que troba un valid.
//si no el troba, llavors ja fica comamand not found.

//Ej: ls esta dintre dels paths, pero si jo creo un programa que es diu ls que li dic que quan sexecuti escrigui hola a la terminal i el deixo a la carpeta en el que estic, quan escrigui ls posara hola, perque abans de mirar els paths ha trobat un programa qu ees diu ls dins de la propia carpeta

//com per comprobar que esta a la propia carpeta he de construir una ruta absoluta, ja que la he construit la puc utilitzar per passarli al execve. em servira tant passarli el comando a secas o aquesta ruta absoluta.



//SI LE PASO A MINISHELL /bin/ls, PERO EN REALIDAD ESE PATH ESTA INCOMPLETO.... Y ME LO HACE BIEN



int count_commands(t_general *data)
{
	int n;
	t_token *tmp;

	n = 0;
	tmp = data->first_token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			n++;
		tmp = tmp->next;
	}
	return (n + 1);
}


int	get_children(t_general *data)
{
	int			i;
	int 		n;
	pid_t		pid;
	t_token 	*tkn;
	/*BORRAR*/ char *type[] = {"null", "pipe", "stdin_redirection", "stdin_double_redirection", "stdout_redirection", "stdout_double_redirection", "file" "cmd"};

	printf ("\n# Get children:\n");
	i = 0;
	n = count_commands(data); // = numero de pipes + 1
	printf ("   La cantidad de hijos es: %d\n", n);

	tkn = data->first_token;
	printf ("\n# Revisar tokens para hacer fork en cuanto sea un comando\n");
	while (i < n)
	{
		printf("   Tipo de token: %d (%s)\n", tkn->type, type[tkn->type]); 
		if (tkn->type != FILE && tkn->type != CMD ) // !!!! ESTO EN REALIDAD NO SERA ASI, PORQUE CUANDO ENCUENTRE UN SEPARADOR TENDRE QUE HACER COSAS, NO SOLO PASAR ADELANTE
		{
			tkn = tkn->next;
			printf("   Tipo de token: %d (%s)\n", tkn->type, type[tkn->type]); 
		}
		if (n > 1)
			create_pipe(data); //genero los fd de la pipe
		create_pipe(data); //genero los fd de la pipe
		pid = fork();
		if (pid == -1)
		{
			perror_message(NULL, "Fork");
			return (0); 
		}
		tkn->pid = pid; // hasta aqui, lo van haciendo paralelamente padre e hijo, por eso ambos tienen el pid y es la manera de comunicarse entre ellos
		if (pid == 0) // tengo que decirle que lo que viene a continuacion se haga en el hijo, distinguir entre el hijo y padre a traves del pid.
		{
			//tkn->pid = pid; //necesito guardarme el pid para luego checkear el status del proceso en el waitpid.
			create_child(data, tkn);
		}
		data->reading_pipe_fd = data->pipe_fd[0];
		tkn = tkn->next;
		i++;

	}
	return (1);
}

t_command *create_command (t_general *data)
{
	t_cmd 	*new_cmd;

	new_cmd = malloc (sizeof(t_cmd) * 1);
	if (!new_cmd)
	{
		//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
		return (NULL);
	}
	return (new_cmd);

}

void put_new_list_cmd_node (t_general *data, t_command *new_cmd)
{
	t_cmd  *tmp_cmd;

	if (!data->first_cmd)
	{
		data->first_cmd = new_cmd;
		//data->first_cmd->back = NULL; CREO QUE NO LO NECESITO
		data->first_cmd->next = NULL;
	}
	else
	{
	//	(addback)
		tmp_cmd = data->first_cmd;
		while (tmp_cmd && tmp_cmd->next)
			tmp_cmd = tmp_cmd->next;
		tmp_cmd->next = new_cmd;
		//new_cmd->back = tmp_cmd; CREO QUE NO LO NECESITO
		new_cmd->next = NULL;
	}
}

t_redir *create_redir (t_general *data)
{
	t_redir 	*new_redir;

	new_redir = malloc (sizeof(t_redir) * 1);
	if (!new_redir)
	{
		//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
		return (NULL);
	}
	return (new_redir);

}

void put_new_list_redir_node (t_general *data, t_redir *new_redir)
{
	t_redir  *tmp_redir;

	if (!data->first_redir)
	{
		data->first_redir = new_redir;
		//data->first_redir->back = NULL; CREO QUE NO LO NECESITO
		data->first_redir->next = NULL;
	}
	else
	{
	//	(addback)
		tmp_redir = data->first_redir;
		while (tmp_redir && tmp_redir->next)
			tmp_redir = tmp_redir->next;
		tmp_redir->next = new_redir;
		//new_redir->back = tmp_redir; CREO QUE NO LO NECESITO
		new_redir->next = NULL;
	}
}

int get_command (t_general *data, t_token *first_token, t_cmd *first_cmd)
{
	t_token *count_tkn;
	t_token *tmp_tkn;
	t_cmd 	*new_cmd;
	t_redir *new_redir;
	int  	count;
	int i;

	count_tkn = first_token;
	tmp_tkn = first_token;
	count = 0;
	i = 0;
	while (tmp_tkn)
	{
		//SIEMPRE VA A HABER MINIMO 1 COMANDO O PUEDE QUE HAYA SOLO UN TOKEN SIN NADA???? SI NO HUBIERA NADA NO HABRIA TOKENS DIRECTAMENTE, SI LLEGO AQUI MINIMO HABRA UN COMANDO, NO?????
		
		//crear un cmd 
		new_cmd = create_command (data);
		if (!new_cmd)
		{
			//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
			//CUIDADO NO HACER DOUBLE FREE
			return (0);
		}
		
		//ubico el nuevo cmd
		put_new_list_cmd_node (data, new_token);
		
		//contar cuantos argumentos tiene el comando 
		while (count_tkn && count_tkn->type != PIPE)
		{
			if (count_tkn->back && (count_tkn->back->type == PIPE || count_tkn->back->type == CMD || count_tkn->back->type == FILE))
				count++;
			count_tkn = count_tkn->next;
		}
				
		//crear el malloc para los argumentos
		if (count != 0)
		{
			new_cmd->argv = malloc (sizeof (char *) * (count + 1));
			if (!new_cmd->argv) 
				//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
				return (0)
		}
		
		//rellenar contenido del comando en si (argumentos y redirecciones)
		while (tmp_tkn->type != PIPE)
		{
			
			if (tmp_tkn && tmp_tkn->type == CMD)
			{
				new_cmd->argv[i] = ft_strdup (tmp_tkn->content)
				if (!new_cmd->argv[i])
				{
					//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
					return (0);
				}
				i++;
			}
			if (tmp_tkn && tmp_tkn->type == FILE)
				continue;
			else
			{
				//crear un nodo redireccion 
				new_redir = create_redir (data);
				if (!new_redir)
				{
					//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
					//CUIDADO NO HACER DOUBLE FREE
					return (0);
				}
				
				//ubico el nuevo nodo
				put_new_list_redir_node (data, new_redir); // SE PUEDE OPTIMIZAR PASANDO UN PUNTERO VOID Y ASI USAR LA MISMA FUNCION? O PASO? TENGO LA MISMA FUNCION 3 VECES CON DIFERENTES ESTRUCTURAS

				//rellenar nuevo nodo
				new_redir->type = tmp_tkn->type;
				new_redir->file_name = ft_strdup(tmp_tkn->next->content);
				if (!new_redir->file_name)
				{
					//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
					return (0);
				}
			}
			tmp_tkn = tmp_tkn->next;
		}
		count_tkn = count_tkn->next;
		tmp_tkn = tmp_tkn->next;
	}







//Cuando en pipex poniamos exit (1), es 1 porque es el valor que solemos dar cuando fallan procesos internos tipo malloc, fork, dup2... 
//En el return del main hacemos lo mismo

int executor (t_general *data)
{
	printf (GREEN"\n******************* EXECUTOR *******************\n"END);
	
	if (get_matrix_env (data, data->env_lst) == 0)
		return (0); // TENGO QUE EMPEZAR EL NUEVO READLINE? O NO Y SIGO
	if (get_all_paths(data->env_lst, data) == 0)
		return (0); // TENGO QUE EMPEZAR EL NUEVO READLINE? O NO Y SIGO       // Voy al siguiente readline porque si falla sera por un malloc, entonces puede que a la siguiente salga bien.
	if (get_command(data, data->first_token, data->first_cmd) == 0)
		return (0); // TENGO QUE EMPEZAR EL NUEVO READLINE? O NO Y SIGO 
// UNA VEZ OBTENIDOS LOS COMANDOS, PODRIA BORRAR LA ESTRUCTURA TOKEN, NO????
	if (get_children(data) == 0)
		return (0);// TENGO QUE EMPEZAR EL NUEVO READLINE? O NO Y SIGO
	father_status(data);
	free_data_paths (data->paths); //Creo unos paths con malloc, y al acabar los tengo que eliminar, independientemente de que el comando exista o no. Lo hago en el padre porque lo creo en el padre, el hijo tiene una copia, no tiene que destruirlo.
	return (1);
}

//Para contar cuantos hijos tiene que haber: El mismo que tokens tipo no separator



//los builtins que modifican las variables de entorno tienen que 
//hacerlo en el padre, porque sino no lo harian

//execute dicen que recibe doble puntero y que es mejor que los 
//builtins trabajen con doble puntero para que el executer ejecute como 
//tal o lo mande a builtins si hace falta, que pueda hacerlo con strncmp 
//sin tener que reconvertir variables 

