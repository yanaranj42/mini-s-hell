/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/17 19:42:13 by mfontser         ###   ########.fr       */
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


// En el caso de que el token sea < inFILE_REDIRECTION cat, dejar que se ejecute el < inFILE_REDIRECTION, y luego reconvertir el token a cat (lo machaco)



//FUNCION TEMPORAL PARA DEBUGAR. LUEGO BORRAR
void debug_cmd(t_cmd *cmd, int num)
{
	int i;
	t_redir *redir = cmd->first_redir;
	char *type[] = {"null", "PIPE", "INPUT", "HEREDOC", "OUTPUT", "APPEND", "FILE_REDIRECTION", "CMD_ARGV"};

	i = 0;
	
	printf("\n    >> Contenido del comando %d:\n", num);
	while (cmd->argv[i])
	{
		printf("        argv[%d] = |%s|\n", i, cmd->argv[i]);
		i++;
	}
	printf("\n");
	if (cmd->first_redir == NULL)
		printf("        No hay redirecciones\n");
	else
	{
		i = 0;
		while (redir)
		{
			printf("        redir[%d] es de tipo = |%s|\n", i, type[redir->type]);
			printf("        nombre del archivo = |%s|\n", redir->file_name);
			i++;
			redir = redir->next;
		}
	}

}


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
	//De momento solo pongo comandos, como no hay archivos de los que leer no tengo que cambiar el stdin, leera de la linea de comandos y se guardara el resultado
	printf("dup2 output fd %d\n", data->pipe_fd[1]);
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

int	check_write_file(t_cmd *cmd, t_redir *redir)
{
	int		flags;
	mode_t	mode;

	flags = O_CREAT | O_TRUNC | O_WRONLY;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
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
	if (check_write_file(cmd, redir) == 0)
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


int	create_child(t_general *data, t_cmd *cmd, int i, int n)
{

	//COMO SABER SI EL HIJO TIENE QUE PODER LEER O ESCRIBIR? Por el toquen que tiene a izquierda o derecha

	//cada token corresponde a una cosa, no me voy a encontrar que en un toquen hay un archivo, un comando y una flag, o es archivo o es comando, y separados por separadores
	t_redir *redir;
	
	write(1, PURPLE, ft_strlen(PURPLE)); // BORRAR
	write(1, "\nSOY UN HIJO\n", 13); // BORRAR
	write(1, "\n# Checkear comandos:\n", 22); // BORRAR
	write(2, END, ft_strlen(END)); // BORRAR
	//si no hago esperar al padre mientras el hijo hace cosas, el padre sigue y me aparece el siguiente readline en medio, por eso cuando el hijo acaba no me aparece el prompt, porque ya estoy ahi
	check_cmd(cmd, data->paths);
	printf ("\n");
	printf ("valor de i: %d\n", i);
	printf ("   >>> Cmd path antes del execve: %s\n", cmd->path);
	if (n > 1 && i != 0) //NECESARIO??? CONFRONTA CON LAS REDIRECCIONES?
		prepare_input_pipe(data); // le digo que el input del comando sea el fd 0 de la pipe 
	if (n > 1 && i < (n - 1)) //NECESARIO??? CONFRONTA CON LAS REDIRECCIONES?
		prepare_output_pipe(data); // redirecciono el output del comando hacia el fd 1 de la pipe
	redir = cmd->first_redir;
	while (redir)
	{
		if (redir->type == 4) // >
			check_output_redir (cmd, redir);
		// if (cmd->first_redir->type == 5) // >>
		// {

		// }
		if (cmd->first_redir->type == 2) // <
			check_input_redir (cmd, redir);
		// if (cmd->first_redir->type == 3) // <<
		// {

		// }
		redir = redir->next;
	}
	printf(PURPLE"\n# Excecve:\n"END"\n");
	//Si en algun momento tengo problemas en el programa, DESCOMENTAR para comprobar si el problema son los fd. Si descomento y sigue fallando, sabre que no son los fd.
	//for (int i = 3; i < 10240; i++) // Esto cierra todos lo fd que no sean el 0, 1 o 2. Esto me asegura que no tenga ningun despiste de dejarme un fd abierto antes de ejcutar el comando, ya que si quedara alguno aberto, algunos cmd no se llegarian a terminar de ejecutar porque se quedarian esperando
	//	close(i);
	if (execve(cmd->path, cmd->argv, data->env_matrix) == -1) // si el execve no puede ejecutar el comando con la info que le hemos dado (ej: ls sin ningun path), nos da -1. El execve le dara un valor que recogera el padre para el exit status.
	{
		perror_message(NULL, "Execve failed");
		exit(1);
	}
	return (1);
}

//!!!REVISAR:
// EL PERROR, LO UNICO QUE NO GESTIONA ES EL COMMAND NOT FOUND, HAY QUE HARDCODEARLO. SI NO ENCUENTRA EL COMANDO EN EL PATH, COMMAND NOT FOUND
// AHORA ESTOY DICIENDO QUE SI NO ENCUENTRA EL PATH O NO EXISTE, QUE EL PATH ES EL PROPIO COMANDO Y LO INTENTE IGUAL, Y ME DICE ARCHIVO NO ENCONTRADO, PERO ESO ESTA MAL.
// ESO TENGO QUE HACERLO ASI SOLO SI ME PASAN EL COMANDO CON LA RUTA ABSOLUTA, SI HAY UNA / EN EL COMANDO (QUE SIGNIFICA QUE ESTOY PASANDO UNA RUTA ABSOLUTA, O INTENTANDOLO). EN ESE MOMENTO SI QUE INDEPENDIENTEMENTE DE QUE NO LO ENCUENTRE SE LO TENGO QUE PASAR AL PERROR PARA QUE ME PASE EL ERROR DE FILE_REDIRECTION NOT FOUND


//El execve solo ejecuta comandos de los que tiene el path. Aunque haya path, comandos del sistema como cd, export o unset, no los encuentra como el resto, por lo tanto tampoco los puede ejecutar.


//Quan entro un comando al sistema primer mira si esta la ruta que li passo, ja sigui absoluta o relativa. si li passo el comando a secas, la ruta relativa es ./comando, busca el comando a la carpeta que jo estic
//quan jo li entro a secas un comando la terminal enten que es una ruta relativa a la propia carpeta. En el cas de que no ho trobi, ho busca en els diferents del enviroment i va probant desquerra a dreta fins que troba un valid.
//si no el troba, llavors ja fica comamand not found.

//Ej: ls esta dintre dels paths, pero si jo creo un programa que es diu ls que li dic que quan sexecuti escrigui hola a la terminal i el deixo a la carpeta en el que estic, quan escrigui ls posara hola, perque abans de mirar els paths ha trobat un programa qu ees diu ls dins de la propia carpeta

//com per comprobar que esta a la propia carpeta he de construir una ruta absoluta, ja que la he construit la puc utilitzar per passarli al execve. em servira tant passarli el comando a secas o aquesta ruta absoluta.



//SI LE PASO A MINISHELL /bin/ls, PERO EN REALIDAD ESE PATH ESTA INCOMPLETO.... Y ME LO HACE BIEN


// //Como lo hacia antes:
// int count_commands(t_general *data)
// {
// 	int n;
// 	t_token *tmp;

// 	n = 0;
// 	tmp = data->first_token;
// 	while (tmp)
// 	{
// 		if (tmp->type == PIPE)
// 			n++;
// 		tmp = tmp->next;
// 	}
// 	return (n + 1);
// }


int count_commands(t_general *data)
{
	int n;
	t_cmd *tmp;

	n = 0;
	tmp = data->first_cmd;
	while (tmp)
	{
		n++;
		printf ("comando %d\n: %s\n", n, tmp->argv[0]);
		tmp = tmp->next;
	}
	return (n);
}

int	get_children(t_general *data)
{
	int			i;
	int 		n;
	t_cmd 		*cmd;

	printf ("\n# Get children:\n");
	i = 0;
	//n = count_commands(data); // = numero de pipes + 1
	n = count_commands(data);
	
	printf ("   La cantidad de hijos es: %d\n", n);

	cmd = data->first_cmd;
	printf ("\n# Revisar tokens para hacer fork en cuanto sea un comando\n");
	while (i < n)
	{
		//fd [0] = lectura
		//fd [1] = escritura
		if (data->pipe_fd[0] >= 0)
		{
				data->next_cmd_input_fd = dup(data->pipe_fd [0]); // el fd output del primer comando sera el fd input del segundo comando y lo va a leer del fd[0], el de lectura. Con el dup creo una copia del fd, ya que si solo lo igualo hago que los dos apunten al mismo espacio de memoria, y si cierro uno jodo el otro. Asi son dos espacios de memoria distintos
				close(data->pipe_fd[0]); // tengo que cerrar este fd en el padre, pero despues de hacer la copia
				
		}
				
		if (n > 1 && i < (n - 1))
		{
			create_pipe(data); //genero los fd de la pipe
			printf ("Los fd de la pipe %d son:\n   *%d\n   *%d\n", i, data->pipe_fd[0], data->pipe_fd[1]);
			
		}
		cmd->pid = fork();
		if (cmd->pid == -1)
		{
			//SI FALLA EL FORK TENGO QUE HACER CLOSE DE LOS FD???
			perror_message(NULL, "Fork");
			return (0); 
		}
		// hasta aqui, lo van haciendo paralelamente padre e hijo, por eso ambos tienen el pid y es la manera de comunicarse entre ellos
	
		if (cmd->pid == 0) // tengo que decirle que lo que viene a continuacion se haga en el hijo, distinguir entre el hijo y padre a traves del pid.
		{
			//cmd->pid = pid; //necesito guardarme el pid para luego checkear el status del proceso en el waitpid.
			create_child(data, cmd, i, n);
		}
		close(data->pipe_fd[1]); // cierro el fd en el padre. Si no cierro la pipe de escritura del cmd anterior, el siguiente cmd piensa que aun le pueden escribir cosas y se queda eternamente escuchando desde el fd 0, por eso no me escribe nunca el resultado, porque el wc hasta que no acaba el archivo no escribe nada, en cambio otros comandos como el cat escriben linea a linea, por eso el cat si funcionaba igualmente.
		close(data->next_cmd_input_fd); // cierro el fd en el padre
		cmd = cmd->next;
		i++;

	}
	return (1);
}

t_cmd *create_command (void) //(t_general *data) SEGURAMENTE PARA ALGUN FREE
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

void put_new_list_cmd_node (t_general *data, t_cmd *new_cmd)
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

t_redir *create_redir (void) //(t_general *data) SEGURAMENTE PARA ALGUN FREE
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

void put_new_list_redir_node (t_cmd *new_cmd, t_redir *new_redir)
{
	t_redir  *tmp_redir;

	if (!new_cmd->first_redir)
	{
		new_cmd->first_redir = new_redir;
		//new_cmd->first_redir->back = NULL; CREO QUE NO LO NECESITO
		new_cmd->first_redir->next = NULL;
	}
	else
	{
	//	(addback)
		tmp_redir = new_cmd->first_redir;
		while (tmp_redir && tmp_redir->next)
			tmp_redir = tmp_redir->next;
		tmp_redir->next = new_redir;
		//new_redir->back = tmp_redir; CREO QUE NO LO NECESITO
		new_redir->next = NULL;
	}
}

int get_command (t_general *data, t_token *first_token)
{
	t_token *count_tkn;
	t_token *tmp_tkn;
	t_cmd 	*new_cmd;
	t_redir *new_redir;
	int  	count;
	int i;
	// char *type[] = {"null", "PIPE", "INPUT", "HEREDOC", "OUTPUT", "APPEND", "FILE_REDIRECTION", "CMD_ARGV"}; // BORRAR
	int num; //borrar

	count_tkn = first_token;
	tmp_tkn = first_token;
	num = 1; // borrar
	printf("\n# Get commands\n");
	while (tmp_tkn)
	{
		//SIEMPRE VA A HABER MINIMO 1 COMANDO O PUEDE QUE HAYA SOLO UN TOKEN SIN NADA???? SI NO HUBIERA NADA NO HABRIA TOKENS DIRECTAMENTE, SI LLEGO AQUI MINIMO HABRA UN COMANDO, NO?????
		
		//crear un cmd 
		new_cmd = create_command (); //(data);
		if (!new_cmd)
		{
			//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
			//CUIDADO NO HACER DOUBLE FREE
			return (0);
		}
		
		//ubico el nuevo cmd
		put_new_list_cmd_node (data, new_cmd);
		
		//contar cuantos argumentos tiene el comando 
		
		count = 0;
		// printf ("\n Argumentos del comando %d:\n", num);
		while (count_tkn && count_tkn->type != PIPE)
		{
			if (count_tkn->type == CMD_ARGV)
				count++;
			// printf("    %s (tipo: %s)\n", count_tkn->content, type[count_tkn->type]);
			count_tkn = count_tkn->next;
		}
		// printf("  Cantidad final de argumentos que van a formar el comando: |%d|\n", count);	
		
		//crear el malloc para los argumentos
		if (count != 0)
		{
			new_cmd->argv = malloc (sizeof (char *) * (count + 1));
			if (!new_cmd->argv) 
				//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
				return (0);
		}

		//rellenar contenido del comando en si (argumentos y redirecciones)
		new_cmd->first_redir = NULL; // PARA INICIALIZAR EN CADA NODO, NO?
		i = 0;
		while (tmp_tkn && tmp_tkn->type != PIPE)
		{
			if (tmp_tkn && tmp_tkn->type == CMD_ARGV)
			{
				new_cmd->argv[i] = ft_strdup (tmp_tkn->content);
				if (!new_cmd->argv[i])
				{
					//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
					return (0);
				}
				i++;
			}
			
			// else if (tmp_tkn && tmp_tkn->type == FILE_REDIRECTION)
			// 	continue;
			else
			{
				//crear un nodo redireccion 
				new_redir = create_redir (); //(data);
				if (!new_redir)
				{
					//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
					//CUIDADO NO HACER DOUBLE FREE
					return (0);
				}
				
				//ubico el nuevo nodo
				put_new_list_redir_node (new_cmd, new_redir); // SE PUEDE OPTIMIZAR PASANDO UN PUNTERO VOID Y ASI USAR LA MISMA FUNCION? O PASO? TENGO LA MISMA FUNCION 3 VECES CON DIFERENTES ESTRUCTURAS

				//rellenar nuevo nodo
				new_redir->type = tmp_tkn->type;
				printf("tipo de redireccion: %d\n", new_redir->type);
				new_redir->file_name = ft_strdup(tmp_tkn->next->content);
				printf("nombre archivo: %s\n", new_redir->file_name);
				if (!new_redir->file_name)
				{
					//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
					return (0);
				}
				tmp_tkn = tmp_tkn->next;
			}
			if (tmp_tkn)
				tmp_tkn = tmp_tkn->next;
		}
		new_cmd->argv[i] = NULL;
		debug_cmd(new_cmd, num); // PARA CHECKEAR, LUEGO BORRAR
		num++;
		if (count_tkn) // si en el ultimo while ya ha llegado al final, aqui le estaria forzando a avanzar mas y me da segfault
			count_tkn = count_tkn->next;
		if (tmp_tkn) // si en el ultimo while ya ha llegado al final, aqui le estaria forzando a avanzar mas y me da segfault
			tmp_tkn = tmp_tkn->next;
	}
	return (1);
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
	if (get_command(data, data->first_token) == 0)
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

