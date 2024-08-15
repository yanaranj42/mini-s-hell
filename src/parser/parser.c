/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:05:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/15 21:32:53 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


void debug_token(t_token *token, int num)
{
	int i;

	i = 0;
	printf("  >> Contenido del token %d:\n", num);
	printf("     argc = %d\n", token->argc);
	while (token->argv[i])
	{
		printf("     argv[%d] = |%s|\n", i, token->argv[i]);
		i++;
	}
	printf("     token actual: %p\n", token);
	printf("     next apunta a %p\n", token->next);
	printf("     back apunta a %p\n\n", token->back);
}


int parser(char *line, t_general *data)
{
	int i;
	int j;
	int count;
	t_token *new_token;// voy creando los tokens en esta variable temporal. Una vez creados los guardo donde toquen, si no existe first token lo guardare ahi, sino recorrere la lista hasta el ultimo nodo y lo enlazare ahi
	t_token *tmp_token;
	int num = 1; //BORRAR
//< echo hola que tal | ls -la
//Opciones de hacerlo:
//puedo ir guardando un cacho en pretoken, creo token, destruyo pretoken y sigo recorriendo para coger el siguiente cacho
//primero saber cuantos cachos hay en la linea, hacer un array de strings de la cantidad de cachos que voy a necesitar, recorrer e ir metiendo cachos en ese array y luego ya crear los tokens.
	i = 0;
	printf ("\n******************* PARSER *******************\n");
	printf ("#Creacion de tokens:\n");
	while (line[i])
	{
		printf(" TOKEN %d\n", num);
		//guardo en pretoken
		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			data->pretoken = strjoinchar (data->pretoken, line[i]);
			if (line[i + 1] == '<' || line[i + 1] == '>' || line[i + 1] == '|')
			{
				i++;
				continue;
			}
			i++;
		}
		else
		{
			while (line[i] && line[i] != '<' && line[i] != '>' && line[i] != '|') // el or es que mientras se cumpla alguna de las condiciones, el and es que se cumplan todas. Si pongo or, si encuentra un separador <, como no es | ni >, la condicion se cumple y sigue entrando en el while.
			{
				data->pretoken = strjoinchar (data->pretoken, line[i]);
				i++;
			}
		}
		//creo un token
		new_token = malloc (sizeof(t_token) * 1); //aqui estoy creando un token, lo que me devuelve el malloc es la direccion de memoria, que la guardo en first token (que antes era null). first token ya esta creado desde el momento que creo data, pero first token no es un token, es solo un puntero que almacenara una direccion de memoria
		if (!new_token)
		{
			//si falla la creacion de un token tendre que liberar los tokens ya creados de la lista (si existe) y liberar pretoken, no???
			printf("Error: New token malloc fail\n");
			free(data->pretoken);
			i = 0;
			if (data->first_token)
				while (data->first_token)
				{
					tmp_token = data->first_token->next;
					while (data->first_token->argv && data->first_token->argv[i]) //REVISAR QUE CONTENT HAY QUE LIBERAR DE CADA NODO DE LOS TOKENS
					{
						free(data->first_token->argv[i]);
						i++;
					}
					free(data->first_token->argv);
					free(data->first_token);
					data->first_token = tmp_token;
				}
			return (0);
		}

		//ubico el nuevo token
		if (!data->first_token)
		{
			data->first_token = new_token;
			data->first_token->back = NULL;
			data->first_token->next = NULL;
		}
		else
		{
		//	(addback)
			tmp_token = data->first_token;
			while (tmp_token && tmp_token->next)
				tmp_token = tmp_token->next;
			tmp_token->next = new_token;
			new_token->back = tmp_token;
			new_token->next = NULL;
		}
	
		//genero el contenido del token
		
		printf ("  Pretoken final: |%s|\n\n", data->pretoken); 
		new_token->argv = ft_split(data->pretoken, ' '); //el split me crea la matriz, lo que hago es guardar la direccion de memoria de esa matriz en argv
		//new_token->argv = ft_token_split(data->pretoken, ' ', data); //el split me crea la matriz, lo que hago es guardar la direccion de memoria de esa matriz en argv
		//dentro del split tengo que controlar que no haya comillas abiertas o cerradas cuando evaluo el espacio.
		//contar palabras teniendo en cuenta que todo lo de dentro de las comillas es una sola.
		if (!new_token->argv)
		{
			printf("Error: There have been problems doing the argv token split\n");
			free(data->pretoken);
			i = 0;
			while (data->first_token)
			{
				tmp_token = data->first_token->next;
				while (data->first_token->argv && data->first_token->argv[i]) //REVISAR QUE CONTENT HAY QUE LIBERAR DE CADA NODO DE LOS TOKENS
				{
					free(data->first_token->argv[i]);
					i++;
				}
				free(data->first_token->argv);
				free(data->first_token);
				data->first_token = tmp_token;
			}
			return (0);
		}
		count = 0;
		j = 0;
		while (new_token->argv[j])
		{
			j++;
			count++;
		}
		new_token->argc = count;
		debug_token(new_token, num); // PARA CHECKEAR, LUEGO BORRAR
		num++; //BORRAR
		//destruyo pretoken para volver a crearlo en la siguiente vuelta
		free(data->pretoken);
		data->pretoken = NULL;
		printf("\ncontenido de line[i] despues de la vuelta: |%c|\n\n", line [i]);
	}
	return (1);
}