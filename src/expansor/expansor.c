/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/20 15:47:17 by mfontser         ###   ########.fr       */
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


t_xtkn *create_xtoken (void) //(t_general *data) SEGURAMENTE PARA ALGUN FREE
{
	t_xtkn 	*tmp_xtkn;

	tmp_xtkn = malloc (sizeof(t_xtkn) * 1);
	if (!tmp_xtkn)
	{
		//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
		return (NULL);
	}
	return (tmp_xtkn);

}

void put_new_list_xtoken_node (t_general *data, t_xtkn *xtkn)
{
	t_xtkn  *tmp_xtkn;

	if (!data->first_xtkn)
	{
		data->first_xtkn = xtkn;
		data->first_xtkn->back = NULL;
		data->first_xtkn->next = NULL;
	}
	else
	{
	//	(addback)
		tmp_xtkn = data->first_xtkn;
		while (tmp_xtkn && tmp_xtkn->next)
			tmp_xtkn = tmp_xtkn->next;
		tmp_xtkn->next = xtkn;
		xtkn->back = tmp_xtkn; 
		xtkn->next = NULL;
	}
}



t_xtkn *token_to_xtoken(t_token *token, t_general *data)
{
	t_xtkn	*xtkn;

	xtkn = create_xtoken ();
	if (!xtkn)
	{
		//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
		//CUIDADO NO HACER DOUBLE FREE
		return (0);
	}
	
	//relleno xtkn
	xtkn->content = NULL;
	xtkn->type = token->type;


	//ubico el nuevo cmd
	put_new_list_xtoken_node (data, xtkn);
	return(xtkn);
		
}


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

int check_expansor_variable_exists (char *tmp, t_env *env)
{
	t_env *env_tmp;

	env_tmp = env;

	if (!tmp)
		return (0);
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0))
			return (1);
		env_tmp = env_tmp->next;
	}

	return (0);
}

int expansor_variable_has_space (char *tmp, t_env *env)
{
	t_env *env_tmp;

	env_tmp = env;

	if (!tmp)
		return (0);
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0))
		{
			if (ft_strchr(env_tmp->value, ' '))
				return (1);
		}
		env_tmp = env_tmp->next;
	}
	return (0);
}

int change_expansor_variable(t_xtkn *xtkn, char *tmp, t_env *env)
{
	t_env *env_tmp;
	int i;

	i = 0;;
	env_tmp = env;
	if (!tmp)
		return (0);
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0))
		{
			while (env_tmp->value[i])
			{
				if (env_tmp->value[i] == '"')
				{
					xtkn->content = strjoinchar (xtkn->content, 30); //Cambio las quotes por un valor no imprimible antes de expandir. Asi no tendre problemas al gestionar el split y saber que comillas quitar
					if (!xtkn->content)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
				}
				else if (env_tmp->value[i] == '\'')
				{
					xtkn->content = strjoinchar (xtkn->content, 31); //Cambio las miniquotes por un valor no imprimible antes de expandir. Asi no tendre problemas al gestionar el split y saber que comillas quitar
					if (!xtkn->content)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
				}
				else 
				{
					xtkn->content = strjoinchar (xtkn->content, env_tmp->value[i]);
					if (!xtkn->content)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
				}
				i++;
			}
		}
		env_tmp = env_tmp->next;
	}
	return(1);
}

int build_expanded_content (t_xtkn	*xtkn, t_token *token, int exit_status, t_env *env, t_general *data)
{
	int i;
	char *tmp;
	char *exit_number;
	
	printf ("\n🟠 Toquen \n"); //BORRAR
	printf("\n# Expandir contenido del token |%s|\n", token->content);
	i = 0;
	tmp = NULL; //IMPORTANTISIMO inicializar, sino la primera vez que hago el strjoinchar coge un valor random y no funciona bien.
	xtkn->heardoc_expansion = 1;
	init_quote_values(data);
	while (token->content[i])
	{
		account_quotes (token->content[i], data);
		if (data->qdata.quotes == 1 || data->qdata.miniquotes == 1)
			xtkn->heardoc_expansion = 0;
		if(token->content[i] == '$')
		{
			i++;
			if (token->content[i] && (ft_isalpha(token->content[i]) == 1 || token->content[i] == '_'))
			{
				while (token->content[i] && (ft_isalpha(token->content[i]) == 1 || ft_isdigit(token->content[i]) == 1 || token->content[i] == '_'))
				{
					tmp = strjoinchar (tmp, token->content[i]);
					if (!tmp)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
					
					i++;
				}
				printf ("  Contenido del xtkn después del $: |%s|\n", tmp);
				if (data->qdata.miniquotes == 1)
				{
					xtkn->content = adapted_strjoin(xtkn->content, tmp);
					if (!xtkn->content)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
				}
				else if (data->qdata.quotes == 1)
				{
					if (xtkn->back && xtkn->back->type == HEREDOC) // Si antes tiene un heredoc quiere decir que es un limitador y no se tiene que expandir
					{
						xtkn->content = strjoinchar (xtkn->content, '$');
						if (!xtkn->content)
						{
							//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
							return (0);
						}
						xtkn->content = adapted_strjoin(xtkn->content, tmp);
						if (!xtkn->content)
						{
							//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
							return (0);
						}
					}
					else
					{
						if (check_expansor_variable_exists (tmp, env) == 0)
						{
							xtkn->content = adapted_strjoin(xtkn->content, "");
							if (!xtkn->content)
							{
								//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
								return (0);
							}
						}
						else
						{
							if (change_expansor_variable(xtkn,tmp, env) == 0)
							{
								//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
								return (0);
							}
						}	
					}	
				}
				else
				{
					if (xtkn->back && xtkn->back->type == HEREDOC) // Si antes tiene un heredoc quiere decir que es un limitador y no se tiene que expandir
					{
						xtkn->content = strjoinchar (xtkn->content, '$'); 
						if (!xtkn->content)
						{
							//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
							return (0);
						}
						xtkn->content = adapted_strjoin(xtkn->content, tmp);
						if (!xtkn->content)
						{
							//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
							return (0);
						}
					}
					else
					{
						if (check_expansor_variable_exists (tmp, env) == 0)
						{
							//si hay un $nada y luego cosas, no entra y simplemente no se mete nada en content. Si lo siguiente es un $nada y ya no hay nada mas, entonces metera de golpe los dos $nada juntos en el contenido. Si en cambio despues de este segundo hay algo mas, simplemente saltara y se metera unicamente lo que hay a continuacion
							if (!xtkn->content && !token->content[i] && token->back && (token->back->type == INPUT || token->back->type == OUTPUT || token->back->type == APPEND))
							{
								printf("entro\n");
								xtkn->content = ft_strdup (token->content);
								if (!xtkn->content)
								{
									//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
									return (0);
								}
							}
							// else if (xtkn->content && ft_strchr(xtkn->content, '$') && ((token->back && token->back->type == INPUT) || (token->next && (token->next->type == OUTPUT || token->next->type == APPEND))))
							// {
							// 	xtkn->content = ft_strdup (token->content);
							// 	if (!xtkn->content)
							// 	{
							// 		//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
							// 		return (0);
							// 	}
							// }
						
							// else
							// {
							// 	printf ("entro\n");
							// 	xtkn->content = adapted_strjoin(xtkn->content, NULL);
							// 	if (!xtkn->content)
							// 	{
							// 		//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
							// 		return (0);
							// 	}
							// } 
						}
						else
						{
							if (expansor_variable_has_space(tmp, env) && xtkn->type == FILE_REDIRECTION)
							{
								xtkn->content = ft_strdup (token->content);
								if (!xtkn->content)
								{
									//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
									return (0);
								}
							}
							else if (change_expansor_variable(xtkn,tmp, env) == 0)
							{
								//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
								return (0);
							}
						}
					}	
				}
			}
			else if (token->content[i] && token->content[i] == '?')
			{
				exit_number = ft_itoa (exit_status);
				if (!exit_number)
				{
					//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
					return (0);
				}
				xtkn->content = adapted_strjoin(xtkn->content, exit_number);
				if (!xtkn->content)
				{
					//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
					free (exit_number);
					return (0);
				}
				free (exit_number);
				i++;
			}
			else if (token->content[i] && ft_isdigit(token->content[i]) == 1)
			{
				if (data->qdata.miniquotes == 1)
				{
					xtkn->content = strjoinchar (xtkn->content, '$');
					if (!xtkn->content)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
					xtkn->content = strjoinchar (xtkn->content, token->content[i]);
					if (!xtkn->content)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
					i++;
				}
				else 
				{
					if (token->content[i] == '0')
					{
						xtkn->content = adapted_strjoin(xtkn->content, "✌️ bash");
						if (!xtkn->content)
						{
							//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
							return (0);
						}
						i++;
					}
					else 
					{
						xtkn->content = adapted_strjoin(xtkn->content, "");
						if (!xtkn->content)
						{
							//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
							return (0);
						}
						i++;
					}
				}
				
			}
			else if (token->content[i] && token->content[i] == '"' && data->qdata.miniquotes == 0 && data->qdata.quotes == 0)
			{
				account_quotes (token->content[i], data);
				xtkn->content = strjoinchar (xtkn->content, token->content[i]);
				i++;

			}
			else if (token->content[i] && token->content[i] == '\'' && data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
			{
				account_quotes (token->content[i], data);
				xtkn->content = strjoinchar (xtkn->content, token->content[i]);
				i++;
			}
			else if (token->content[i] && (token->content[i] == '"' || token->content[i] == '\''))
			{
				account_quotes (token->content[i], data);
				xtkn->content = strjoinchar (xtkn->content, '$');
				if (!xtkn->content)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
				xtkn->content = strjoinchar (xtkn->content, token->content[i]);
				if (!xtkn->content)
				{
					//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
					return (0);
				}
				i++;
			}
			free(tmp);
			tmp = NULL;
			continue ;
		}
		xtkn->content = strjoinchar (xtkn->content, token->content[i]);
		if (!xtkn->content)
		{
			//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
			return (0);
		}
		i++;
	}
	printf("  hay que expandir en heredoc?: %d\n", xtkn->heardoc_expansion);
	return (1);
}

t_xtkn *expand_xtkn(t_token *token, int exit_status, t_env *env, t_general *data)
{
	t_xtkn	*xtkn;

	xtkn = token_to_xtoken(token, data);
	if (!xtkn)
	{
		//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
		return (NULL);
	}
	if (build_expanded_content (xtkn, token, exit_status, env, data) == 0)
	{
		//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
		return (NULL);
	}
	return (xtkn);
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
		//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
		return (0);
	}
	i = 0;
	while (splited_content[i])
		i++;

	if (i > 1)
	{
		free (xtkn->content); //NECESARIO???
		xtkn->content = ft_strdup (splited_content[0]);
		printf ("\nRETOKENIZACION\n");
		i = 1;
		while (splited_content[i])
		{
			tmp_xtkn = create_xtoken ();
			if (!tmp_xtkn)
			{
				//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
				//CUIDADO NO HACER DOUBLE FREE
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
		{
			//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
			return (0);
		}
		i++;
	}
	free (xtkn->content);
	xtkn->content = ft_strdup (tmp);
	if (!xtkn->content)
	{
		//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
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
			return (0);
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
			//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
			return (0);
		}
		printf (" *-._.-* Token expandido |%s|\n\n", xtkn->content);
		if (xtkn->content)
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

	if (finish_xtkn (data->first_xtkn, data) == 0) // RECORRER LA LISTA ENTERA, POR CADA UNO LE QUITO QUOTES Y LE CAMBIO LOS CHARS NO IPRIMIBLES, Y PASO AL SIGUIENTE	
		return (0);
		
	free_tokens_list(data);

	//Al acabar de crear todos los xtokens puedo liberar los tokens
	return (1);
}


// DESPUES DEL SPLIT PIERDO TOKENS PPOR EL CAMINO
