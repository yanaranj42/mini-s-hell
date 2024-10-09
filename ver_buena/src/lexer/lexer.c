/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:39:24 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/29 13:37:35 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void delete_spaces (t_general *data)
{
	char *tmp;

	tmp = data->line;
	data->line = ft_strtrim(data->line, " ");
	//el readline crea un malloc, por lo que a esta funcion le paso un malloc. Luego strtrim crea otro para alocar el nuevo string y yo igualo el viejo al nuevo. Tengo que liberar el malloc viejo, porque el puntero line ahora apuntara al nuevo malloc y el viejo se quedaria perdido
	free(tmp);
}


int review_closed_quotes (t_general *data)
{
	int i;
 
	i = 0;
	init_quote_values(data);
	while (data->line[i])
	{
		printf ("     char %d --> %c\n", i, data->line[i]);
		if (data->line[i] == '"' && data->qdata.miniquotes == 0) //solo cambia el valor si el otro tipo de comillas no esta abierto ya, porque sino seran un char normal
		{
			printf("        He encontrado unas comillas dobles\n");
			if (data->qdata.quotes == 0)
				data->qdata.quotes = 1;
			else if(data->qdata.quotes == 1)
				data->qdata.quotes  = 0;
			printf("        Valor de quotes: %d\n", data->qdata.quotes);
		}
		if (data->line[i] == '\'' && data->qdata.quotes == 0) //como poner el char ' ??? si pongo \' estoy escapando el caracter, osea estoy diciendo que lo interprete como un caracter normal, y no como el metacaracter que representa. La contrabarra me permite escapar metacaracteres
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


int delete_useless_spaces (t_general *data)
{
	int i;

	i = 0;
	printf ("\n#Limpieza de espacios inutiles:\n");
	init_quote_values(data);
	while (data->line[i])
	{
		if ((data->line[i] == '"' && data->qdata.miniquotes == 0) || (data->line[i] == '\'' && data->qdata.quotes == 0))
			account_quotes (data->line[i], data);
		else if (data->line[i] == ' ' && data->line[i + 1] == ' ' && data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
		{
			i++;
			continue;
		}
		data->pretoken = strjoinchar (data->pretoken, data->line[i]);
		if (!data->pretoken)
			return (0);
		i++;
	}
	printf("# Linea de comandos final: |%s|\n", data->pretoken);
	free(data->line); //libero la linea original con los espacios inutiles
	data->line = data->pretoken; // le digo que line sea la nueva linea transformada
	data->pretoken = NULL; // por si acaso ya pongo este puntero en en null porque ya no lo necesito mas, ya tengo line para acceder al contenido del lexer
	return (1);
} 


int lexer (t_general *data)
{
	printf (GREEN"\n******************* LEXER *******************\n"END);
	delete_spaces(data);
	printf ("# Linea de comandos despues de strtrim: |%s|\n", data->line);
	if (data->line[0] == '\0') // como digo contenido al estar en una estructura????
		return (0);
	printf ("\n# Revision de comillas:\n");
	if (review_closed_quotes (data) == 0)
	{
		printf("Error: The quotes are not closed properly\n"); // pensar si mensaje de error y continue, o no cerrar hasta que ponga comillas 
		return (0);
	}
	//limpiar espacios inutiles 
	if (delete_useless_spaces(data) == 0)
	{
		printf("Error: There have been problems cleaning useless spaces\n");
		return (0);
	}
	return (1);
}
