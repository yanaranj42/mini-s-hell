/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:39:24 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/09 14:24:38 by mfontser         ###   ########.fr       */
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

	printf ("contenido de pretoken: |%s|\n", str);
	printf ("char a añadir: |%c|\n\n", c);
	if (str == NULL && c == '\0')
		return (NULL);
	if (str)
		new_str = malloc(sizeof(char) * (ft_strlen(str) + 1 + 1));
	else
		new_str = malloc(sizeof(char) * (1 + 1));
	if (!new_str)
		return (NULL);
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
	printf ("%s\n", new_str);
	return (new_str);
} 
//OPTIMIZAR ????




void delete_useless_spaces (char **line, t_general *data)
{
	int i;
	char *tmp;

	i = 0;
	printf ("\n#Limpieza de espacios inutiles:\n");
	init_quote_values(data);
	while (line[0][i])
	{
		tmp = data->pretoken;
		if (line[0][i] == '"' && data->qdata.miniquotes == 0)
		{
			if (data->qdata.quotes == 0)
				data->qdata.quotes = 1;
			else if(data->qdata.quotes == 1)
				data->qdata.quotes  = 0;
		}
		else if (line[0][i] == '\'' && data->qdata.quotes == 0)
		{
			if (data->qdata.miniquotes == 0)
				data->qdata.miniquotes = 1;
			else if(data->qdata.miniquotes == 1)
				data->qdata.miniquotes  = 0;
		}
		else if (line[0][i] == ' ' && line[0][i + 1] == ' ' && data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
		{
			i++;
			continue;
		}
		data->pretoken = strjoinchar (data->pretoken, line[0][i]);
		free(tmp);
		i++;
	}
	printf("# Linea de comandos final: |%s|\n", data->pretoken);
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
		printf("Las comillas no estan cerradas\n"); // pensar si mensaje de error y continue, o no cerrar hasta que ponga comillas 
		return (0);
	}
	//limpiar espacios inutiles 
	delete_useless_spaces(line, data);
	return (1);
}

//si ya es un puntero, porque tengo que pasar un puntero al puntero para 
//cambiar el contenido en todas partes?????

//line en la estructura mejor?