/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:00:25 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/08 12:06:59 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int main(int argc, char ** argv, char **env)
{
	char 		*line;
	t_general	data; 

	(void)argc;
	(void)argv;

	init_data_values(&data); 
	if (get_own_env(env, &data) == 0)
		return (0);
	

	while (1)
	{
		line = readline("DrackyShell: ");
		if (!line) //temporal. Para evitar segfault al comparar si line no existe
		{
			break;
		}
		if (ft_strncmp("exit", line, 5) == 0) //temporal
		{
			free(line);
			break;
		}
		add_history (line); // para poder acceder al historial de comandos
		printf("%s\n", line); // borrar

		//LEXER

		//PARSER

		pseudoparser(line, &data);   //pseudaparser sencillo que solo me coja un comando spliteado por espacios
		//EXPANDER

		//EXECUTOR
		//pseudoexecutor que no es capaz de ejecutar comandos encadenados por separador, pero si me podria ejecutar un export a=3 y luego env (dos comandos por separado: primero canviar el enviroment y luego ver los cambios al imprimirlo), podria probar export 3=3 que tiene que sacar un error. Asi sin haber terminado el parser podemos empezar a probar los built-ins
		pseudoexecutor(&data); 

		// limpiar los tokens
		free(line);
	}
	free_before_end(&data);
    return (0);	
}


//Cuando haces un EOF (end-of-file, osease un control D), le estas mandando un NULL, osea line sera  igual a NULL. Como ahora hago un strncmp de line sin protegerlo, al mandarle un NULL me da segfault
//Unset PATH -> borra el path

//Creo la copia del enviroment al principio y luego trabajo con la copia, por eso esa funcion esta fuera del while, solo lo hago una vez
//Dentro del minishell, como puedo ejecutar mas de una orden las variables de entorno pueden cambiar a medida que esta minishell en marcha, porque puedo hacer exports y unsets. Por eso no puedo guardarme el path al principio y checkear el path solo al principio (como hacia en pipex), ya que puede cambiar. Tengo que poder consultar el path de mi enviroment a cada comando que le entre, por si ha cambiado en algun comando anterior
//Ej: en pipex, si hacemos echo hola | export a=2 | echo $a
//Como el export lo estoy haciendo en un hijo, estoy añadiendo la variable de entorno a en ese hijo, pero cuando el siguiente hijo quiera imprimir el valor de a, para el no existe esa variable.
//En minishell como puedo ejecutar mas de una linea, si hago un primer comando que sea: export a=3; y en el siguiente pongo: echo hola | export a=2 | echo $a; esto me imprimira 3, porque el export del hijo sigue estando solo en el hijo.
//El echo hola no se imprime porque al haber una pipe, el resultado de ese comando se redirige al stdin del siguiente comando (no se muestra por pantalla). La redireccion la he hecho, pero el comando export no coge ningun stdin, por lo que lo ignora.

