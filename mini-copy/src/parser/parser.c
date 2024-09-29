/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:05:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/27 12:28:37 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//FUNCION TEMPORAL PARA DEBUGAR. LUEGO BORRAR
/* void debug_token(t_token *token, int num)
{
	int i;
	char *type[] = {"null", "pipe", "stdin_redirection", "stdin_double_redirection", "stdout_redirection", "stdout_double_redirection", "no_separator"};

	i = 0;
	while (token->argv[i])
	{
		i++;
	}
	printf("     tipo de token: %d (%s)\n", token->type, type[token->type]);
	printf("     token actual: %p\n", token);
	printf("     next apunta a %p\n", token->next);
	printf("     back apunta a %p\n\n", token->back);
} */

//version antigua planteada inicialmente (mal):
// void take_pretoken (t_general *data, int *i)
// {
// 	if (data->line[*i] == '<' || data->line[*i] == '>' || data->line[*i] == '|')
// 		{
// 			data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
// 			if (data->line[*i + 1] == '<' || data->line[*i + 1] == '>' || data->line[*i + 1] == '|')
// 			{
// 				*i++;
// 				continue;
// 			}
// 			*i++;
// 		}
// 		else
// 		{
// 			while (data->line[*i] && data->line[*i] != '<' && data->line[*i] != '>' && data->line[*i] != '|') // el or es que mientras se cumpla alguna de las condiciones, el and es que se cumplan todas. Si pongo or, si encuentra un separador <, como no es | ni >, la condicion se cumple y sigue entrando en el while.
// 			{
// 				data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
// 				*i++;
// 			}
// 		}
// 		//falta proteger
// 		//necesito un retorno de si falla un malloc, uno de si tengo que hacer continue y otro por si no tengo que hacer continue
// 		//me puedo mandar una flag como puntero para que me diga si tengo que hacer continue o no.
// 		//uso el return de 0 - 1 por si falla el malloc o no.
// }



//Cuando llego a pretoken solo puedo encontrarme espacio, o separador o otra cosa. Por lo que lo de las cuotes lo gestiono directamente en el ultimo caso, no hace falta que lo repita por separado, por si empieza en comilas o las encuentra mas adelante. TOdo en el caso de "otros" y listo
//Version buena pero larga:

// int take_pretoken (t_general *data, int *i)
// {

// 	if (data->line[*i] == ' ')
// 		(*i)++;
// 	printf ("valor de quotes 1: %d\n", data->qdata.quotes);

// 	if (data->line[*i] == '<' || data->line[*i] == '>' || data->line[*i] == '|')
// 	{
// 		data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
// 		if (!data->pretoken)
// 			return (0);
// 		if (data->line[*i] == '<' && data->line[*i + 1] == '<')
// 		{
// 			(*i)++;
// 			data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
// 		}
// 		else if (data->line[*i] == '>' && data->line[*i + 1] == '>')
// 		{
// 			(*i)++;
// 			data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
// 		}
// 		if (!data->pretoken)
// 			return (0);
// 		(*i)++;
// 	}

// 	else
// 	{
// 		//while (data->line[*i] && is_real_separator(data->line[*i], data->qdata))
// 		while (data->line[*i] && data->line[*i] != '<' && data->line[*i] != '>' && data->line[*i] != '|') // el or es que mientras se cumpla alguna de las condiciones, el and es que se cumplan todas. Si pongo or, si encuentra un separador <, como no es | ni >, la condicion se cumple y sigue entrando en el while.
// 		{
// 			account_quotes (data->line[*i], data);
// 			printf ("valor de quotes 4: %d\n", data->qdata.quotes);
// 			if (data->qdata.quotes == 1)
// 			{
// 				data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
// 					if (!data->pretoken)
// 						return (0);
// 					(*i)++;
// 				while (data->line[*i] && data->line[*i] != '"')
// 				{
// 					data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
// 					if (!data->pretoken)
// 						return (0);
// 					(*i)++;
// 				}
// 				account_quotes (data->line[*i], data);
// 				printf ("valor de quotes 5: %d\n", data->qdata.quotes);
// 				data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
// 				if (!data->pretoken)
// 					return (0);
// 				(*i)++;
// 			} 
// 			else if (data->qdata.miniquotes == 1)
// 			{
// 				data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
// 					if (!data->pretoken)
// 						return (0);
// 					(*i)++;
// 				while (data->line[*i] && data->line[*i] != '\'')
// 				{
// 					data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
// 					if (!data->pretoken)
// 						return (0);
// 					(*i)++;
// 				}
// 				account_quotes (data->line[*i], data);
// 				printf ("valor de quotes 6: %d\n", data->qdata.quotes);
// 				data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
// 				if (!data->pretoken)
// 					return (0);
// 				(*i)++;
// 			}
// 			else
// 			{
// 				data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
// 				if (!data->pretoken)
// 					return (0);
// 				(*i)++;
// 			}
// 		}
// 	}
// 		//falta proteger
// 		//uso el return de 0 - 1 por si falla el malloc o no.

// 		// Antes tenia puesto que si despues de un separador encontraba otro separador, que volviera a empezar el bucle de parser y fuera acumulando todos los simbolos en un token. Pero en realidad, tengo que tratarlo como tokens separados, ya que bash acepta los simbolos de < y > por pares, y en cuanto a la pipe, va de una en una, ya que dos seguidas lo interpreta como un or y eso es parte del bonus, nosotras si encontramos varias pipes seguidas las interpretamos como si fuera esto "| |", pipes individuales
// 	return (1);
// }

int is_real_separator(char c, t_general *data)
{
	account_quotes (c, data);
	if ((c == '<' || c == '>' || c == '|') && data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
		return (1);
	return (0);
}

int take_pretoken (t_general *data, int *i)
{

	if (data->line[*i] == ' ')
		(*i)++;

	if (data->line[*i] == '<' || data->line[*i] == '>' || data->line[*i] == '|')
	{
		data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
		if (!data->pretoken)
			return (0);
		if (data->line[*i] == '<' && data->line[*i + 1] == '<')
		{
			(*i)++;
			data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
		}
		else if (data->line[*i] == '>' && data->line[*i + 1] == '>')
		{
			(*i)++;
			data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
		}
		if (!data->pretoken)
			return (0);
		(*i)++;
	}

	else
	{
		while (data->line[*i] && is_real_separator(data->line[*i], data) == 0)
		{
			data->pretoken = strjoinchar (data->pretoken, data->line[*i]);
			if (!data->pretoken)
				return (0);
			(*i)++;
		}
	}
		//falta proteger
		//uso el return de 0 - 1 por si falla el malloc o no.

		// Antes tenia puesto que si despues de un separador encontraba otro separador, que volviera a empezar el bucle de parser y fuera acumulando todos los simbolos en un token. Pero en realidad, tengo que tratarlo como tokens separados, ya que bash acepta los simbolos de < y > por pares, y en cuanto a la pipe, va de una en una, ya que dos seguidas lo interpreta como un or y eso es parte del bonus, nosotras si encontramos varias pipes seguidas las interpretamos como si fuera esto "| |", pipes individuales
	return (1);
}

// asdf asdf | asf " asdf<aasdf" asd


t_token *create_token (t_general *data)
{
	t_token *new_token;

	new_token = malloc (sizeof(t_token) * 1); //aqui estoy creando un token, lo que me devuelve el malloc es la direccion de memoria, que la guardo en first token (que antes era null). first token ya esta creado desde el momento que creo data, pero first token no es un token, es solo un puntero que almacenara una direccion de memoria
	if (!new_token)
	{
		//si falla la creacion de un token tendre que liberar los tokens ya creados de la lista (si existe) y liberar pretoken, no???
		printf("Error: New token malloc fail\n");
		free(data->pretoken);
		
		if (data->first_token)
			free_tokens_list(data);
		return (NULL);
	}
	return (new_token);
}

void put_new_list_node (t_general *data, t_token *new_token)
{
	t_token *tmp_token;

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
}


t_token *create_token_content (t_general *data, t_token *new_token)
{
	int i;
	int count;

	new_token->argv = ft_token_split(data->pretoken, ' ', data); //el split me crea la matriz, lo que hago es guardar la direccion de memoria de esa matriz en argv
	//new_token->argv = ft_split(data->pretoken, ' '); //el split me crea la matriz, lo que hago es guardar la direccion de memoria de esa matriz en argv
	//dentro del split tengo que controlar que no haya comillas abiertas o cerradas cuando evaluo el espacio.
	//contar palabras teniendo en cuenta que todo lo de dentro de las comillas es una sola.
	if (!new_token->argv)
	{
		printf("Error: There have been problems doing the argv token split\n");
		free(data->pretoken);
		free_tokens_list(data);
		return (NULL);
	}
	count = 0;
	i = 0;
	while (new_token->argv[i])
	{
		i++;
		count++;
	}
	new_token->argc = count;
	return (new_token);
}

void classify_token_type (t_token *new_token)
{
	if (ft_strncmp ("|", new_token->argv[0], 2) == 0 && new_token->argc == 1)
		new_token->type = PIPE;
	else if (ft_strncmp ("<", new_token->argv[0], 2) == 0 && new_token->argc == 1)
		new_token->type = STDIN_REDIRECTION;
	else if (ft_strncmp ("<<", new_token->argv[0], 3) == 0 && new_token->argc == 1)
		new_token->type = STDIN_DOUBLE_REDIRECTION;
	else if (ft_strncmp (">", new_token->argv[0], 2) == 0 && new_token->argc == 1)
		new_token->type = STDOUT_REDIRECTION;
	else if (ft_strncmp (">>", new_token->argv[0], 3) == 0 && new_token->argc == 1)
		new_token->type = STDOUT_DOUBLE_REDIRECTION;
	else
		new_token->type = NO_SEPARATOR;
}

int parser(t_general *data)
{
	int i;
	t_token *new_token;// voy creando los tokens en esta variable temporal. Una vez creados los guardo donde toquen, si no existe first token lo guardare ahi, sino recorrere la lista hasta el ultimo nodo y lo enlazare ahi
	int num = 1; //BORRAR

//< echo hola que tal | ls -la
//Opciones de hacerlo:
	//puedo ir guardando un cacho en pretoken, creo token, destruyo pretoken y sigo recorriendo para coger el siguiente cacho
	//primero saber cuantos cachos hay en la linea, hacer un array de strings de la cantidad de cachos que voy a necesitar, recorrer e ir metiendo cachos en ese array y luego ya crear los tokens.
	i = 0;
	printf ("\n******************* PARSER *******************\n");
	while (data->line[i])
	{		
		//guardo en pretoken
		if (take_pretoken (data, &i) == 0)
		{
			printf("Error: There have been problems preparing tokens\n");
			return (0);
		}		
		//creo un token
		new_token = create_token (data);
		if (!new_token)
			return (0);

		//ubico el nuevo token
		put_new_list_node (data, new_token);
		
		
		//genero el contenido del token

		//estas dos maneras siguientes me sirven independientemente que en create token content me duevuelva el puntero token o un 0 - 1 de si ha funcionado bien o mal. Teniendo en cuenta que eso puedo hacerlo porque destruyo token dentro de la funcion, sino tendria un leak de memoria, porque me ha entrado un token, ha fallado el argv, pero el token hay que destruirlo, porque ya estaba creado.
		//manera 1:
		if(!create_token_content (data, new_token)) //REVISAR SI ESTO SE PUEDE O TIENE SENTIDO
			return (0);
			//Si me devuelvo la direccion de memoria de new_token despues de pasar por create token content, contara como true. Si me devuelve null contara como false la condicion.
		
		//manera 2:
		// new_token = create_token_content (data, new_token); //REVISAR SI ESTO SE PUEDE O TIENE SENTIDO
		// if(!new_token)
		// 	return (0);

		
		
		//Esto esta mal, porque si me devuelve nul, intento acceder al argv de null y eso da segfault:
		// new_token = create_token_content (data, new_token); //REVISAR SI ESTO SE PUEDE O TIENE SENTIDO
		// if (!new_token->argv)     NULL->argv (no tiene sentido)

		classify_token_type (new_token);
		//debug_token(new_token, num); // PARA CHECKEAR, LUEGO BORRAR
		num++; //BORRAR
		//destruyo pretoken para volver a crearlo en la siguiente vuelta
		free(data->pretoken);
		data->pretoken = NULL;
	}
	
	return (1);
}
