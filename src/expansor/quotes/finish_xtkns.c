/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_xtkns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/04 20:32:09 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


void change_non_printable_chars(t_xtkn	*xtkn)
{
	int i;

	i = 0;
	while (xtkn->content[i])
	{
		if(xtkn->content[i] == 30)	
			xtkn->content[i] = '"';
		if(xtkn->content[i] == 31)	
			xtkn->content[i] = '\'';
		i++;
	}
}


int build_content_without_quotes (t_xtkn *xtkn, t_general *data, char **tmp)
{
	int i;

	i = 0;
	while (xtkn->content[i])
	{
		account_quotes (xtkn->content[i], data);
		if(xtkn->content[i] == '"' && data->qdata.miniquotes == 0)
		{
			i++;
			continue ;
		}
		if(xtkn->content[i] == '\'' && data->qdata.quotes == 0)
		{
			i++;
			continue ;
		}
		
		*tmp = strjoinchar (*tmp, xtkn->content[i]);
		if (!*tmp)
			return (0);
		i++;
	}
	return (1);
}


int remove_quotes(t_xtkn	*xtkn, t_general *data)
{
	char *tmp;
	
	//printf("\n# Remove quotes\n");
	init_quote_values(data);
	tmp = ft_strdup (""); //IMPORTANTISIMO inicializar, le meto un string vacio para que ya empiece con \0 en caso de que no haya nada mas que las comillas y el contenido se quede en \0, en vez de NULL. Ahora de este modo tengo un malloc. Es lo que me interesa, porque si esta entre comillas, aunque dentro no tenga nada, tengo que mantener el xtoken con un \0 dentro.
	if (!tmp)
		return (0);
	printf ("valor tmp %s\n", tmp);
	if (build_content_without_quotes (xtkn, data, &tmp) == 0)
		return (0);
	printf ("valor tmp %s\n", tmp);
	free (xtkn->content);
	xtkn->content = ft_strdup (tmp);
	if (!xtkn->content)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	//printf ("  Contenido del xtoken FINAL: %s\n\n\n", xtkn->content);
	return (1);
}

int finish_xtkns (t_xtkn	*first_xtkn, t_general *data)
{
	t_xtkn	*xtkn;

	xtkn = first_xtkn;
	printf ("#Lista final de xtokens:\n");
	while (xtkn)
	{
		if (remove_quotes (xtkn, data) == 0)
		{
			printf("Error: There have been problems finishing the expansion\n");
			return (0);
		}
		//FALTA CAMBIAR LOS CHARS NO IMPRIMIBLES POR COMILLAS SIMPLES O DOBLES
		change_non_printable_chars (xtkn);
		printf (" ----> Token final |%s|\n\n", xtkn->content);
		xtkn = xtkn->next;
	}
	return (1);
}
