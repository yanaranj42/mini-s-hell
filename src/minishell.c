/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:00:25 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/13 16:15:09 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char 		*line; // mejor dentro de la estructura????????
	t_general	data; 

	(void)argv; // que hacemos con esto???

	if (argc != 1)
		return (0);
	init_values(&data, env);
	while (1)
	{
		line = readline("🔥 ÐrackyŠhell 🔥 ▶ ");
		if (!line) //temporal. Para evitar segfault al comparar si line no existe, ej cuando le pongo ctr + D
		{
			break;
		}
		if (ft_strncmp("exit", line, 5) == 0) //temporal
		{
			free(line);
			break;
		}
		add_history (line); // para poder acceder al historial de comandos
		printf("\nLinea de comando original: |%s|\n", line); // borrar

		//LEXER
		if (lexer(&line, &data) == 0) //Un char * es un string, si lo quiero pasar por referencia tengo que pasar un puntero al string, osea un char **, por eso paso la direccion de memoria de line
			continue; // para volver a empezar el while
		
		//PARSER
		pseudoparser(line, &data); //pseudaparser sencillo que solo me coja un comando spliteado por espacios
		//EXPANDER

		//EXECUTOR
		//pseudoexecutor que no es capaz de ejecutar comandos encadenados por separador, pero si me podria ejecutar un export a=3 y luego env (dos comandos por separado: primero canviar el enviroment y luego ver los cambios al imprimirlo), podria probar export 3=3 que tiene que sacar un error. Asi sin haber terminado el parser podemos empezar a probar los built-ins
		pseudoexecutor(&data); 

		// limpiar los tokens
		free_tokens_list (data.first_token); //--> sera la funciona que llamare cuando tenga lista, iterare sobre la lista e ire limpiando nodos llamando a la funcion basica de free token
		//no paso la direccion de memoria porque estoy pasando first token, que ya es un puntero, y quiero limpiar lo que hay a donde apunta ese puntero. Me da igual que en la funcion que limpie lo que llegue sea una copia del puntero, y no el puntero original.
		//el hermano tonto y el original apuntan al sitio que quiero limpiar, y como al limpiar accedo al contenido, ya se limpia para todos.
		// cuando creo data creo una cajonera que ya tiene dos punteros y donde puedo poner dos direccioens de memoria, osea first token no lo aloco, se crea directamente con data. Si quiero que first token apunte a un token, lo que tengo que hacer es crear el token (malloc), y la direccion se guarda en first token
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

