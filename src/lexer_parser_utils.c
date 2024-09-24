/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:50:06 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/24 17:46:53 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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


//strjoinchar, que una un carácter a un string, y una variable tipo char *pretoken que vaya acumulando los chars para formar el string.

char *strjoinchar (char *str, char c) // METER EN EL LIBFT
{
	int i;
	char *new_str;

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
	while (str && str[i] != '\0') // si no existe str ya me aseguro de que no entre en el while, pongo la condicion la primera a checkear, y al ser un and tienen que cumplirse ambas. si falla la primera no se mira la segunda y no hay peligro de que intente acceder a algo que no existe y pete
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	free (str);
	return (new_str);
} 


// En cuanto a gestionar memoria, antes igualaba una variable temporal a pretoken para que a la siguiente vuelta de entrar en strjoinchar alguien siguiera apuntando al antiguo malloc (porque al entrar en la funcion le digo que cree un nuevo malloc para añadir un nuevo caracter y pretoken apunta al nuevo malloc)
// Entonces, tengo que gestionar que si al entrar a la funcion el malloc falla, si pretoken se convierte en null, que alguien libere lo que habia antes.
// Por otro lado, tengo que asegurarme tambien de que si todo va bien, antes de retornar el nuevo string, se libere el viejo. 
// Asi ya no hace falta usar ningun tmp, que lo usaba solo para poder liberar la memoria antigua.
