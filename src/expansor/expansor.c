/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/29 02:04:08 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//Necesito la lista de tokens que tengo hasta ahora, el exit status hasta ahora y el env.

// Expandir las variables del comando 'cmd' (como una lista de tokens) y divide
// palabras si es necesario. Finalmente, realiza la eliminación de cotizaciones y devuelve el resultado.




// Given a list of tokens, allocates and returns a list of xtokens with its
// environment variables (or exit status) expanded, preserving the original
// token type and setting each character's flags for expanded and quoted status.



int start_xtkns (t_general *data)
{
	t_token *token;
	t_xtkn	*xtkn;

	token = data->first_token;
	while (token)
	{
		xtkn = expand_xtkn(token, data->env_lst, data);
		if (!xtkn)
			return (0);
		printf (" *-._.-* Token expandido |%s|\n\n", xtkn->content);
		if (xtkn->content) // puede que al expandir el contenido haya pasado a ser null, por lo que tendria que quitarlo de la lista, sino miro si hay que splitear
		{
			if (split_xtkn (xtkn, data) == 0)
				return (0);
		}
		else
		{
			if (xtkn->back)
				xtkn->back->next = NULL;
			free(xtkn); //mato el xtoken actual
			xtkn = NULL;
		}			
		token = token->next;
	}
	return (1);
}


// Expands the env variables and $? of the 'commands' and split words if needed.
// Finally, performs quote removal and returns the result.
int expansor (t_general *data)
{
	printf (GREEN"\n******************* EXPANSOR *******************"END);
	
	if (start_xtkns (data) == 0)
	{
		free_expansor (data);
		return (0);
	}
	if (finish_xtkns (data->first_xtkn, data) == 0) // RECORRER LA LISTA ENTERA, POR CADA UNO LE QUITO QUOTES Y LE CAMBIO LOS CHARS NO IPRIMIBLES, Y PASO AL SIGUIENTE	
	{
		free_expansor (data);
		return (0);
	}

	free_tokens_list(data);

	//Al acabar de crear todos los xtokens puedo liberar los tokens
	return (1);
}

