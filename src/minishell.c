/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:00:25 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/22 13:30:35 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int main(int argc, char **argv, char **env)
{
	t_general	data; 

	(void)argv; 

	if (argc != 1)
	{
		printf("To run the program, no parameters are needed other than the executable itself\n");
		return (1); //de normal se usa el return 1 para decir true y el return 0 para decir false, pero en el main, el return 0 indica que todo ha acabado bien y el return 1 (o el numero que sea) para decir que ha habido un error y poder identificar cual, como el exit.
	}
	init_data_values(&data); 
	if (get_own_env(&data, env) == 0)
		return (1); //cortamos programa?????????? NO, REVISAR PARA QUE LA LISTA SEA VACIA EN VEZ DE SALIR
	//Si no hay enviroment, crearse una lista vacia, osea poner el puntero first a null. Esto es lo mas correcto, porque aunque no haya enviroment, hay comandos que siguen pudiendo ejecutarse y puedo crear archivos y meterles cosas. Y quizas empiezo el minishell sin enviroment y a base de exports me lo podria crear



	while (1)
	{
		
		data.line = readline("🔥 ÐrackyŠhell ▶ ");
		//Explicacion:
			// !data.line == NULL --> punetero null
			// data.line[0] = '\0' --> contenido con un caracter nulo
		if (!data.line) //temporal. Para evitar segfault al comparar si line no existe, ej cuando le pongo ctr + D
		{
			//printf ("    Fire can't kill a dragon ❤️‍🔥\n    But.... Winter is coming 🥶\n");
			printf (PURPLE"    The night is dark and full of secrets 🌜 ✨\n\n"END);
			break;
		}
		if (data.line && *data.line)
		{
		if (ft_strncmp("exit", data.line, 5) == 0) //temporal
		{
			printf (ORANGE"    Fire can't kill a dragon ❤️‍🔥\n"END);
			printf (CYAN"              But.... Winter is coming ❄️\n\n"END);
			free(data.line);
			break;
		}
		add_history (data.line); // para poder acceder al historial de comandos
		printf("\nLinea de comando original: |%s|\n", data.line); // borrar

		//LEXER
		if (lexer(&data) == 0) //Un char * es un string, si lo quiero pasar por referencia tengo que pasar un puntero al string, osea un char **, por eso paso la direccion de memoria de line
		{
			free (data.line);
			continue; // para volver a empezar el while
		}
		
		//PARSER
		if (parser(&data) == 0 || check_syntax_errors(&data) == 0) 
		{
			free (data.line);
			continue; // para volver a empezar el while
		}
	

		//EXPANDER


		//EXECUTOR
		//pseudoexecutor que no es capaz de ejecutar comandos encadenados por separador, pero si me podria ejecutar un export a=3 y luego env (dos comandos por separado: primero canviar el enviroment y luego ver los cambios al imprimirlo), podria probar export 3=3 que tiene que sacar un error. Asi sin haber terminado el parser podemos empezar a probar los built-ins
		///pseudoexecutor(&data); 

		//EXIT STATUS!!!!!!!!!!!!
		if (executor (&data)== 0)
		{
			free_matrix_env(&data); //Podria ser que hubiese fallado al hacer el env y ya estuviese freeseado, por lo que estaria volviendo a intentar a hacer un free de lo mismo. Para protegerlo, dentro de la funcion free siempre lo acabo igualando a null, asi aunque vuelva a hacer free del env no habra double free.
			free (data.line);
			free_cmd(&data);
			continue; // para volver a empezar el while
		}
		printf("**************soy la line %s\n", data.line);
		printf (GREEN"\n******************* FREE *******************\n"END);
		// limpiar los tokens
		//free_tokens_list (data.first_token); //--> sera la funciona que llamare cuando tenga lista, iterare sobre la lista e ire limpiando nodos llamando a la funcion basica de free token
		//no paso la direccion de memoria porque estoy pasando first token, que ya es un puntero, y quiero limpiar lo que hay a donde apunta ese puntero. Me da igual que en la funcion que limpie lo que llegue sea una copia del puntero, y no el puntero original.
		//el hermano tonto y el original apuntan al sitio que quiero limpiar, y como al limpiar accedo al contenido, ya se limpia para todos.
		// cuando creo data creo una cajonera que ya tiene dos punteros y donde puedo poner dos direccioens de memoria, osea first token no lo aloco, se crea directamente con data. Si quiero que first token apunte a un token, lo que tengo que hacer es crear el token (malloc), y la direccion se guarda en first token
		
		//En free_tokens limpio solo un token y ademas no pongo first token a null, por eso cuando vuelvo a llamarlo se piensa que ya hay un token existente que a saber a donde apunta y hace cosas raras. Tengo que poner todo a null para la proxima vuelta
		
		//funcion final:
		free_tokens_list(&data);
		free_matrix_env(&data);
		free_cmd(&data);
		free(data.line);
		data.line = NULL;
		}
	}
	free_before_end(&data);
    return (0);	
}


//Cuando haces un EOF (end-of-FILE_REDIRECTION, osease un control D), le estas mandando un NULL, osea line sera  igual a NULL. Como ahora hago un strncmp de line sin protegerlo, al mandarle un NULL me da segfault
//Unset PATH -> borra el path

//Creo la copia del enviroment al principio y luego trabajo con la copia, por eso esa funcion esta fuera del while, solo lo hago una vez
//Dentro del minishell, como puedo ejecutar mas de una orden las variables de entorno pueden cambiar a medida que esta minishell en marcha, porque puedo hacer exports y unsets. Por eso no puedo guardarme el path al principio y checkear el path solo al principio (como hacia en pipex), ya que puede cambiar. Tengo que poder consultar el path de mi enviroment a cada comando que le entre, por si ha cambiado en algun comando anterior
//Ej: en pipex, si hacemos echo hola | export a=2 | echo $a
//Como el export lo estoy haciendo en un hijo, estoy añadiendo la variable de entorno a en ese hijo, pero cuando el siguiente hijo quiera imprimir el valor de a, para el no existe esa variable.
//En minishell como puedo ejecutar mas de una linea, si hago un primer comando que sea: export a=3; y en el siguiente pongo: echo hola | export a=2 | echo $a; esto me imprimira 3, porque el export del hijo sigue estando solo en el hijo.
//El echo hola no se imprime porque al haber una pipe, el resultado de ese comando se redirige al stdin del siguiente comando (no se muestra por pantalla). La redireccion la he hecho, pero el comando export no coge ningun stdin, por lo que lo ignora.

