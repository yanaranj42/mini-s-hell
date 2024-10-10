/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:24:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/10 00:32:52 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "libft.h"


char *check_cmd_current_directory(char *cmd_argv)
{
	char cwd[PATH_MAX]; //Current Working Directory
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if(getcwd(cwd, PATH_MAX))
	{
		tmp = ft_strjoin(cwd, "/"); //cojo el path del directorio actual y pongo / al final
		if (!tmp)
		{
			//MENSAJE ERROR
			return (NULL);
		}
		tmp2 = ft_strjoin(tmp, cmd_argv); // a lo anterior le añado el comando que tengo en la línea
		if (!tmp2)
		{
			free(tmp);
			//MENSAJE ERROR
			return (NULL);
		}
		if (access(tmp2, F_OK) == 0)
		{
			if (access(tmp2, X_OK) == 0)
			{
				free(tmp);
				return (tmp2);
			}
			else
			{
				permission_denied (cmd_argv);
			}
		}
	}
	free(tmp);
	free(tmp2);
	return (NULL);
}

char	*check_cmd_relative_path(char *cmd_argv, char *path)
{
	char	*tmp;
	char	*tmp2;
	tmp = ft_strjoin(path, "/"); //cojo el path entero, pongo / al final
	if (!tmp)
	{
		//MENSAJE ERROR
		return (NULL);
	}
	tmp2 = ft_strjoin(tmp, cmd_argv); // a lo anterior le añado el comando que tengo en la línea
	if (!tmp2)
	{
		free(tmp);
		//MENSAJE ERROR
		return (NULL);
	}
	if (access(tmp2, F_OK) == 0)
	{
		if (access(tmp2, X_OK) == 0)
		{
			free(tmp);
			return (tmp2);
		}
		else
		{
			permission_denied (cmd_argv);
		}
	}
	free(tmp);
	free(tmp2);
	return (NULL);
}


char	*check_cmd_absolut_path(char *cmd_argv) // puede ser que en la linea de comandos nos pasen la ruta absoluta directa, y que no haya path en el enviroment no impediria ejecutar el comando.
{

	if (ft_strchr(cmd_argv, '/'))
	{
		printf("\n       En la linea de comandos me han pasado una RUTA ABSOLUTA...\n");
		if (access(cmd_argv, F_OK) == -1)
		{
			printf ("         ...Pero no existe ese path");
			no_such_file_or_directory (cmd_argv);
			//command_not_found (cmd_argv); /Tiene que llegar al execve para que diga que no encuentra el archivo, por lo que esto no puedo ponerlo
		}
		else if (access(cmd_argv, X_OK) == 0)
		{
			printf ("         ...Y EXISTE EL PATH Y SE PUEDE EJECUTAR!!!\n");
			cmd_argv = ft_strdup(cmd_argv);
			if (!cmd_argv)
			{
				//MIRAR SI TENGO QUE LIBERAR ALGO MAS
				return (NULL);
			}
			return (cmd_argv);
		}
		else
		{
			printf ("         ...Y existe el path pero NO puede ejecutar\n");
			permission_denied (cmd_argv);
		}
	}
	return (NULL);
	//Primero miramos si el comando existe en el primer access. En el caso que exista, en el segundo access miramos si se puede ejecutar. En caso que no se pueda ejecutar ponemos permission denied.
}

char	*check_cmd_access(char **paths, char *cmd_argv)
{
	int		i;
	char	*tmp;
	//int 	flag;

	//flag = 0;
	if (cmd_argv == NULL)
	{
		command_not_found ("''"); // Podria ser argv[0] NULL si en me pasan como parametro el comando '', entonces crearia un token NULL. Como es null, le mando que imprima '', para simbolizarlo por terminal.
		return (NULL);
	}
	tmp = check_cmd_absolut_path(cmd_argv); //aunque haya paths en el enviroment, me pueden haber pasado el comando como ruta absoluta
	if (tmp != NULL)
		return (tmp);
	// if (flag == 1)
	// 	return (NULL);
	i = 0;
	while (paths && paths[i])
	{
		tmp = check_cmd_relative_path(cmd_argv, paths[i]);
		{
			if (tmp != NULL)
				return (tmp);
		}
		i++;
	}
	command_not_found (cmd_argv);
	return (NULL);
}


void	check_cmd(t_cmd *cmd, char **paths)
{
	cmd->path = check_cmd_current_directory(cmd->argv[0]);
	if (!cmd->path)
	{
		if (!paths) // No hay paths en el enviroment
		{
			cmd->path = check_cmd_absolut_path(cmd->argv[0]);
			if (cmd->path == NULL)
				command_not_found (cmd->argv[0]);
		}
		else
			cmd->path = check_cmd_access(paths, cmd->argv[0]);
		//Esto lo ponia para que aunque no encuentre el path, el execve intentara igualmente ejecutar el comando por si era un comando del sistema y no necesitaba path, pero el execve no es capaz (y los casos en los que puede ocurrir son builtins, que se gestionan por otro lado).
		// if (cmd->path == NULL)
		// {
		// 		//cmd->path = cmd->argv[0]; si lo pongo asi tengo dos variables compartiendo el mismo malloc, y si quiero liberar ambas acabare con un double free
		// 	cmd->path = ft_strdup(cmd->argv[0]); //Asi creo un malloc nuevo, en el que path es el comando, para que execve lo pruebe de encontrar (igual esta en la misma carpeta (ej:ejecutar minishell dentro de minishell, de esta manera podra hacerlo) y puede, o simplemente no necesita path para ejecutarlo porque es del sistema)
		// }
	}
}



//Hay comandos que son de sistema e incluso sin PATH en el enviroment o sin ruta absoluta, funcionan, como el cd.
//Por eso, independientemente de que no haya path, intentar ejecutarlo igualmente y coger el valor de retorno del execve y ver si él mismo me pone el command not found.