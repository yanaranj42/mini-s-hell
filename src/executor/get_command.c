/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/24 17:19:18 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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


int get_command (t_general *data, t_xtkn	*first_xtkn)
{
	t_xtkn *count_xtkn;
	t_xtkn *tmp_xtkn;
	t_cmd 	*new_cmd;
	t_redir *new_redir;
	int  	count;
	int i;
	// char *type[] = {"null", "PIPE", "INPUT", "HEREDOC", "OUTPUT", "APPEND", "FILE_REDIRECTION", "CMD_ARGV"}; // BORRAR
	int num; //borrar

	count_xtkn = first_xtkn;
	tmp_xtkn = first_xtkn;
	num = 1; // borrar
	printf("\n# Get commands\n");
	while (tmp_xtkn)
	{
		//SIEMPRE VA A HABER MINIMO 1 COMANDO O PUEDE QUE HAYA SOLO UN TOKEN SIN NADA???? SI NO HUBIERA NADA NO HABRIA TOKENS DIRECTAMENTE, SI LLEGO AQUI MINIMO HABRA UN COMANDO, NO?????
		
		//crear un cmd 
		new_cmd = create_command (); //(data);
		if (!new_cmd)
		{
			free_xtkns_list(data);
			free_matrix_env(data);
			free_data_paths (data);
			free_cmd(data);
			data->exit_status = 1;
			return (0);
		}
		
		//ubico el nuevo cmd
		put_new_list_cmd_node (data, new_cmd);
		
		//contar cuantos argumentos tiene el comando 
		
		count = 0;
		// printf ("\n Argumentos del comando %d:\n", num);
		while (count_xtkn && count_xtkn->type != PIPE)
		{
			if (count_xtkn->type == CMD_ARGV)
				count++;
			// printf("    %s (tipo: %s)\n", count_tkn->content, type[count_tkn->type]);
			count_xtkn = count_xtkn->next;
		}
		printf("  Cantidad final de argumentos que van a formar el comando: |%d|\n", count);	
		
		//crear el malloc para los argumentos
		
		new_cmd->argv = malloc (sizeof (char *) * (count + 1));
		if (!new_cmd->argv) 
		{
			free_xtkns_list(data);
			free_matrix_env(data);
			free_data_paths (data);
			free_cmd(data);
			data->exit_status = 1;
			return (0);
		}

		//rellenar contenido del comando en si (argumentos y redirecciones)
		new_cmd->first_redir = NULL; // PARA INICIALIZAR EN CADA NODO, NO?
		i = 0;
		while (tmp_xtkn && tmp_xtkn->type != PIPE)
		{
			if (tmp_xtkn && tmp_xtkn->type == CMD_ARGV)
			{
				new_cmd->argv[i] = ft_strdup (tmp_xtkn->content);
				if (!new_cmd->argv[i])
				{
					free_xtkns_list(data);
					free_matrix_env(data);
					free_data_paths (data);
					free_cmd(data);
					data->exit_status = 1;
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
					free_xtkns_list(data);
					free_matrix_env(data);
					free_data_paths (data);
					free_cmd(data);
					data->exit_status = 1;
					return (0);
				}
				
				//ubico el nuevo nodo
				put_new_list_redir_node (new_cmd, new_redir); // SE PUEDE OPTIMIZAR PASANDO UN PUNTERO VOID Y ASI USAR LA MISMA FUNCION? O PASO? TENGO LA MISMA FUNCION 3 VECES CON DIFERENTES ESTRUCTURAS

				//rellenar nuevo nodo
				new_redir->type = tmp_xtkn->type;
				printf("tipo de redireccion: %d\n", new_redir->type);
				new_redir->file_name = ft_strdup(tmp_xtkn->next->content);
				printf("nombre archivo: %s\n", new_redir->file_name);
				if (!new_redir->file_name)
				{
					free_xtkns_list(data);
					free_matrix_env(data);
					free_data_paths (data);
					free_cmd(data);
					data->exit_status = 1;
					return (0);
				}
				new_redir->heardoc_expansion = tmp_xtkn->next->heardoc_expansion;
				printf("hay que expandir en heredoc?: %d\n", new_redir->heardoc_expansion);
				tmp_xtkn = tmp_xtkn->next;
			}
			if (tmp_xtkn)
				tmp_xtkn = tmp_xtkn->next;
		}
		new_cmd->argv[i] = NULL;
		debug_cmd(new_cmd, num); // PARA CHECKEAR, LUEGO BORRAR
		num++;
		if (count_xtkn) // si en el ultimo while ya ha llegado al final, aqui le estaria forzando a avanzar mas y me da segfault
			count_xtkn = count_xtkn->next;
		if (tmp_xtkn) // si en el ultimo while ya ha llegado al final, aqui le estaria forzando a avanzar mas y me da segfault
			tmp_xtkn = tmp_xtkn->next;
	}
	return (1);
}
