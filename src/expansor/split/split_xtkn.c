/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_xtkn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/29 00:57:09 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

int enlarge_xtkns_list (t_xtkn	*xtkn, t_general *data, int *i, char **splited_content, t_xtkn	*new_xtkn)
{
	new_xtkn = create_xtoken ();
	if (!new_xtkn)
	{
		printf("Error: There have been problems retokenizing\n");
		free_splited_content (splited_content);
		return (0);
	}

	//relleno xtkn
	new_xtkn->type = xtkn->type;
	new_xtkn->content = ft_strdup (splited_content[*i]);
	
	//ubico el nuevo cmd
	put_new_list_xtoken_node (data, new_xtkn);
	return (1);
}

int retokenize_same_xtoken (t_xtkn	*xtkn, char **splited_content)
{
	free (xtkn->content); 
	xtkn->content = ft_strdup (splited_content[0]);
	if (!xtkn->content)
	{ 
		printf("Error: There have been problems retokenizing\n");
		free_splited_content (splited_content);
		return (0);
	}
	return (1);
}

int split_xtkn(t_xtkn	*xtkn, t_general *data)
{
	//revisar si tengo que hacer split
	//En caso de tener que hacerlo crear nuevo xtoken a continuacion
	//REPETIR EL TIPO DE TOKEN EN LOS NUEVOS TOKENS QUE SE GENEREN POR EL SPLIT
	char **splited_content;
	int i;
	t_xtkn	*new_xtkn; 
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
	new_xtkn = NULL;
	if (i > 1)
	{
		if (retokenize_same_xtoken (xtkn, splited_content) == 0)
			return (0);

		printf ("\nRETOKENIZACION\n");
		i = 1;
		while (splited_content[i])
		{
			if (enlarge_xtkns_list (xtkn, data, &i, splited_content, new_xtkn) == 0)
				return (0);
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
