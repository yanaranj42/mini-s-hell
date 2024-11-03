/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:50:06 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/28 18:49:43 by mfontser         ###   ########.fr       */
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




// En cuanto a gestionar memoria, antes igualaba una variable temporal a pretoken para que a la siguiente vuelta de entrar en strjoinchar alguien siguiera apuntando al antiguo malloc (porque al entrar en la funcion le digo que cree un nuevo malloc para añadir un nuevo caracter y pretoken apunta al nuevo malloc)
// Entonces, tengo que gestionar que si al entrar a la funcion el malloc falla, si pretoken se convierte en null, que alguien libere lo que habia antes.
// Por otro lado, tengo que asegurarme tambien de que si todo va bien, antes de retornar el nuevo string, se libere el viejo. 
// Asi ya no hace falta usar ningun tmp, que lo usaba solo para poder liberar la memoria antigua.
