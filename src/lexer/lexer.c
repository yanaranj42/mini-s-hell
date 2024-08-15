/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:39:24 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/15 20:42:09 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void delete_spaces (char **line)
{
	char *tmp;

	tmp = *line; //es igual al contenido del primer puntero ???
	*line = ft_strtrim(*line, " ");
	//el readline crea un malloc, por lo que a esta funcion le paso un malloc. Luego strtrim crea otro para alocar el nuevo string y yo igualo el viejo al nuevo. Tengo que liberar el malloc viejo, porque el puntero line ahora apuntara al nuevo malloc y el viejo se quedaria perdido
	free(tmp);
}


int review_closed_quotes (char **line, t_general *data)
{
	int i;
 
	i = 0;
	init_quote_values(data);
	while (line[0][i])
	{
		printf ("     char %d --> %c\n", i, line[0][i]);
		if (line[0][i] == '"' && data->qdata.miniquotes == 0) //solo cambia el valor si el otro tipo de comillas no esta abierto ya, porque sino seran un char normal
		{
			printf("        He encontrado unas comillas dobles\n");
			if (data->qdata.quotes == 0)
				data->qdata.quotes = 1;
			else if(data->qdata.quotes == 1)
				data->qdata.quotes  = 0;
			printf("        Valor de quotes: %d\n", data->qdata.quotes);
		}
		if (line[0][i] == '\'' && data->qdata.quotes == 0) //como poner el char ' ??? si pongo \' estoy escapando el caracter, osea estoy diciendo que lo interprete como un caracter normal, y no como el metacaracter que representa. La contrabarra me permite escapar metacaracteres
		{
			printf("        He encontrado unas comillas simples\n");
			if (data->qdata.miniquotes == 0)
				data->qdata.miniquotes = 1;
			else if(data->qdata.miniquotes == 1)
				data->qdata.miniquotes  = 0;
			printf("        Valor de miniquotes: %d\n", data->qdata.miniquotes);
		}
		i++;
	}
	if (data->qdata.quotes == 1 || data->qdata.miniquotes == 1)
		return (0);
	return (1);
}

//como iterar doble puntero??? *line[i] me da overflow


//strjoinchar, que una un carácter a un string, y una variable tipo char *pretoken que vaya acumulando los chars para formar el string.


char *strjoinchar (char *str, char c) // METER EN EL LIBFT
{
	int i;
	char *new_str;

	printf ("     contenido de pretoken: |%s|\n", str);
	printf ("     char a añadir: |%c|\n\n", c);
	if (str == NULL && c == '\0')
		return (NULL);
	if (str)
		new_str = malloc(sizeof(char) * (ft_strlen(str) + 1 + 1));
	else
		new_str = malloc(sizeof(char) * (1 + 1));
	if (!new_str)
	{
		free (str);
		return (NULL);
	}
	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			new_str[i] = str[i];
			i++;
		}
	}
	new_str[i] = c;
	i++;
	new_str[i] = '\0';
	free (str);
	return (new_str);
} 

// En cuanto a gestionar memoria, antes igualaba una variable temporal a pretoken para que a la siguiente vuelta de entrar en strjoinchar alguien siguiera apuntando al antiguo malloc (porque al entrar en la funcion le digo que cree un nuevo malloc para añadir un nuevo caracter y pretoken apunta al nuevo malloc)
// Entonces, tengo que gestionar que si al entrar a la funcion el malloc falla, si pretoken se convierte en null, que alguien libere lo que habia antes.
// Por otro lado, tengo que asegurarme tambien de que si todo va bien, antes de retornar el nuevo string, se libere el viejo. 
// Asi ya no hace falta usar ningun tmp, que lo usaba solo para poder liberar la memoria antigua.


void account_quotes (char c, t_general *data)
{
	if (c == '"' && data->qdata.miniquotes == 0)
		{
			if (data->qdata.quotes == 0)
				data->qdata.quotes = 1;
			else if(data->qdata.quotes == 1)
				data->qdata.quotes = 0;
		}
		else if (c == '\'' && data->qdata.quotes == 0)
		{
			if (data->qdata.miniquotes == 0)
				data->qdata.miniquotes = 1;
			else if(data->qdata.miniquotes == 1)
				data->qdata.miniquotes  = 0;
		}
}

int delete_useless_spaces (char **line, t_general *data)
{
	int i;

	i = 0;
	printf ("\n#Limpieza de espacios inutiles:\n");
	init_quote_values(data);
	while (line[0][i])
	{
		if ((line[0][i] == '"' && data->qdata.miniquotes == 0) || (line[0][i] == '\'' && data->qdata.quotes == 0))
			account_quotes (line[0][i], data);
		else if (line[0][i] == ' ' && line[0][i + 1] == ' ' && data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
		{
			i++;
			continue;
		}
		data->pretoken = strjoinchar (data->pretoken, line[0][i]);
		if (!data->pretoken)
			return (0);
		//Proteger si la funcion devuelve NULL???? romper y salir? Error por terminal?
		i++;
	}
	printf("# Linea de comandos final: |%s|\n", data->pretoken);
	free(*line); //libero la linea original con los espacios inutiles
	*line = data->pretoken; // le digo que line sea la nueva linea transformada
	data->pretoken = NULL; // por si acaso ya pongo este puntero en en null porque ya no lo necesito mas, ya tengo line para acceder al contenido del lexer
	return (1);
} 


int lexer (char **line, t_general *data)
{
	printf ("\n******************* LEXER *******************\n");
	delete_spaces(line);
	printf ("# Linea de comandos despues de strtrim: |%s|\n", *line);
	if (**line == '\0')
		return (0);
	//porque aqui doble puntero para indicar contenido y al imprimir el contenido puntero simple????
	printf ("# Revision de comillas:\n");
	if (review_closed_quotes (line, data) == 0)
	{
		printf("Error: The quotes are not closed properly\n"); // pensar si mensaje de error y continue, o no cerrar hasta que ponga comillas 
		return (0);
	}
	//limpiar espacios inutiles 
	if (delete_useless_spaces(line, data) == 0)
	{
		printf("Error: There have been problems cleaning useless spaces\n"); // pensar si mensaje de error y continue, o no cerrar hasta que ponga comillas 
		return (0);
	}
	return (1);
}

//si ya es un puntero, porque tengo que pasar un puntero al puntero para 
//cambiar el contenido en todas partes?????

//line en la estructura mejor?



//FUNCION VIEJA, USANDO tmp PARA GESTIONAR LA MEMORIA EN EL STRJOINCHAR
// int delete_useless_spaces (char **line, t_general *data)
// {
// 	int i;
// 	char *tmp;

// 	i = 0;
// 	printf ("\n#Limpieza de espacios inutiles:\n");
// 	init_quote_values(data);
// 	while (line[0][i])
// 	{
// 		tmp = data->pretoken;

// 		if ((line[0][i] == '"' && data->qdata.miniquotes == 0) || (line[0][i] == '\'' && data->qdata.quotes == 0))
// 			account_quotes (line[0][i], data);
// 		else if (line[0][i] == ' ' && line[0][i + 1] == ' ' && data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
// 		{
// 			i++;
// 			continue;
// 		}
// 		data->pretoken = strjoinchar (data->pretoken, line[0][i]);
// 		if (!data->pretoken)
// 		{
// 			free(tmp);
// 			return (0);
// 		}
// 		//Proteger si la funcion devuelve NULL???? romper y salir? Error por terminal?
// 		free(tmp);
// 		i++;
// 	}
// 	printf("# Linea de comandos final: |%s|\n", data->pretoken);
// 	free(*line); //libero la linea original con los espacios inutiles
// 	*line = data->pretoken; // le digo que line sea la nueva linea transformada
// 	data->pretoken = NULL; // por si acaso ya pongo este puntero en en null porque ya no lo necesito mas, ya tengo line para acceder al contenido del lexer
// 	return (1);
// } 