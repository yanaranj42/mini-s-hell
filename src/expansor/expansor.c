/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/25 03:22:21 by mfontser         ###   ########.fr       */
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





char	*adapted_strjoin(char *s1, char *s2) //LLEVAR A LIBFT
{
	char	*fusion;
	int		i;
	int		j;

	i = 0;
	if (s1 == NULL)
	{
		s1 = malloc (sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}

	fusion = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!fusion)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	j = 0;
	while (s1[i] != '\0')
		fusion[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		fusion[i++] = s2[j++];
	fusion[i] = '\0';
	free (s1);
	return (fusion);
}



//FUNCION TEMPORAL PARA DEBUGAR. LUEGO BORRAR
void debug_xtoken(t_xtkn	*xtkn, int num)
{
	char *type[] = {"null", "PIPE", "INPUT", "HEREDOC", "OUTPUT", "APPEND", "FILE_REDIRECTION", "CMD_ARGV"};

	printf("\n  >> Contenido del xtkn %d:\n", num);
	printf("     contenido = |%s|\n", xtkn->content);
	printf("     tipo de xtkn: %d (%s)\n", xtkn->type, type[xtkn->type]);
	printf("     xtkn actual: %p\n", xtkn);
	printf("     next apunta a %p\n", xtkn->next);
	printf("     back apunta a %p\n\n", xtkn->back);
}

int split_xtkn(t_xtkn	*xtkn, t_general *data)
{
	//revisar si tengo que hacer split
	//En caso de tener que hacerlo crear nuevo xtoken a continuacion
	//REPETIR EL TIPO DE TOKEN EN LOS NUEVOS TOKENS QUE SE GENEREN POR EL SPLIT
	char **splited_content;
	int i;
	t_xtkn	*tmp_xtkn; // BORRAR
	int num = 0; //BORRAR

	printf("\n# Split\n");
	printf ("  Contenido del xtoken spliteado\n");
	splited_content = ft_token_split(xtkn->content, ' ', data); 
	
	if (!splited_content)
	{
		printf("Error: There have been problems doing the xtoken content split\n");
		return (0);
	}
	i = 0;
	while (splited_content[i])
		i++;

	if (i > 1)
	{
		free (xtkn->content); 
		xtkn->content = ft_strdup (splited_content[0]);
		if (!xtkn->content)
		{
			printf("Error: There have been problems retokenizing\n");
			free_splited_content (splited_content);
			return (0);
		}
		printf ("\nRETOKENIZACION\n");
		i = 1;
		while (splited_content[i])
		{
			tmp_xtkn = create_xtoken ();
			if (!tmp_xtkn)
			{
				printf("Error: There have been problems retokenizing\n");
				free_splited_content (splited_content);
				return (0);
			}

			//relleno xtkn
			tmp_xtkn->type = xtkn->type;
			tmp_xtkn->content = ft_strdup (splited_content[i]);

			//ubico el nuevo cmd
			put_new_list_xtoken_node (data, tmp_xtkn);
			i++;
		}
	}

	t_xtkn *super_tmp = data->first_xtkn; // BORRAR
	while (super_tmp) //BORRAR
	{
		debug_xtoken(super_tmp, num); // PARA CHECKEAR, LUEGO BORRAR
		num++; //BORRAR
		super_tmp= super_tmp->next; // BORRAR
	}
	free_splited_content (splited_content);
	return (1);
}


int remove_quotes(t_xtkn	*xtkn, t_general *data)
{
	char *tmp;
	int i;

	i = 0;
	//printf("\n# Remove quotes\n");
	init_quote_values(data);
	tmp = ft_strdup (""); //IMPORTANTISIMO inicializar, le meto un string vacio para que ya empiece con \0 en caso de que no haya nada mas que las comillas y el contenido se quede en \0, en vez de NULL. Ahora de este modo tengo un malloc. Es lo que me interesa, porque si esta entre comillas, aunque dentro no tenga nada, tengo que mantener el xtoken con un \0 dentro.
	if (!tmp)
		return (0);
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
		
		tmp = strjoinchar (tmp, xtkn->content[i]);
		if (!tmp)
			return (0);
		i++;
	}
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

int finish_xtkn (t_xtkn	*first_xtkn, t_general *data)
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

// Expands the env variables and $? of the 'commands' and split words if needed.
// Finally, performs quote removal and returns the result.
int expansor (t_general *data)
{
	t_token *token;
	t_xtkn	*xtkn;

	printf (GREEN"\n******************* EXPANSOR *******************"END);
	token = data->first_token;
	while (token)
	{
		xtkn = expand_xtkn(token, data->exit_status, data->env_lst, data);
		if (!xtkn)
		{
			data->exit_status = 1;
			free_tokens_list(data);
			free_xtkns_list(data);
			return (0);
		}
		printf (" *-._.-* Token expandido |%s|\n\n", xtkn->content);
		if (xtkn->content) // puede que al expandir el contenido haya pasado a ser null, por lo que tendria que quitarlo de la lista, sino miro si hay que splitear
		{
			if (split_xtkn (xtkn, data) == 0)
			{
				data->exit_status = 1;
				free_tokens_list(data);
				free_xtkns_list(data);
				return (0);
			}
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

	if (finish_xtkn (data->first_xtkn, data) == 0) // RECORRER LA LISTA ENTERA, POR CADA UNO LE QUITO QUOTES Y LE CAMBIO LOS CHARS NO IPRIMIBLES, Y PASO AL SIGUIENTE	
	{
		data->exit_status = 1;
		free_tokens_list(data);
		free_xtkns_list(data);
		return (0);
	}

	free_tokens_list(data);

	//Al acabar de crear todos los xtokens puedo liberar los tokens
	return (1);
}


