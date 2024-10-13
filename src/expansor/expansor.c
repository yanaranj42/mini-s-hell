/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/13 19:57:45 by mfontser         ###   ########.fr       */
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
		//data->first_cmd->back = NULL; CREO QUE NO LO NECESITO
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

	env_tmp = env;
	if (!tmp)
		return (0);
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0))
		{
			xtkn->content = adapted_strjoin(xtkn->content, env_tmp->value);
			if (!xtkn->content)
			{
				//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
				return (0);
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

	i = 0;
	tmp = NULL; //IMPORTANTISIMO inicializar, sino la primera vez que hago el strjoinchar coge un valor random y no funciona bien.
	init_quote_values(data);
	while (token->content[i])
	{
		account_quotes (token->content[i], data);
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
				printf ("contenido tmp |%s|\n", tmp);
				if (data->qdata.miniquotes == 1)
				{
					account_quotes (token->content[i], data);
					xtkn->content = adapted_strjoin(xtkn->content, tmp);
					if (!xtkn->content)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
				}
				else if (data->qdata.quotes == 1)
				{
					account_quotes (token->content[i], data);
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
				else
				{
					account_quotes (token->content[i], data);
					if (check_expansor_variable_exists (tmp, env) == 0)
					{
						if (!xtkn->content && !token->content[i] && ((token->back && token->back->type == INPUT) || (token->next && (token->next->type == OUTPUT || token->next->type == APPEND))))
						{
							xtkn->content = ft_strdup (token->content);
							if (!xtkn->content)
							{
								//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
								return (0);
							}
						}
						else if (xtkn->content && ft_strchr(xtkn->content, '$') && ((token->back && token->back->type == INPUT) || (token->next && (token->next->type == OUTPUT || token->next->type == APPEND))))
						{
							xtkn->content = ft_strdup (token->content);
							if (!xtkn->content)
							{
								//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
								return (0);
							}
						}
					
						else
						{
							xtkn->content = adapted_strjoin(xtkn->content, "");
							if (!xtkn->content)
							{
								//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
								return (0);
							}
						} 
					}
					else
					{
						if (expansor_variable_has_space(tmp, env))
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
			else if (token->content[i] && token->content[i] == '?')
			{
				exit_number = ft_itoa (exit_status);
				xtkn->content = adapted_strjoin(xtkn->content, exit_number);
				if (!xtkn->content)
				{
					//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
					return (0);
				}
				i++;
			}
			else if (token->content[i] && ft_isdigit(token->content[i]) == 1)
			{
				xtkn->content = adapted_strjoin(xtkn->content, "");
				if (!xtkn->content)
				{
					//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
					return (0);
				}
				i++;
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

// void split_xtkn(t_xtkn	*xtkn, t_general *data)
// {


// 	//REPETIR EL TIPO DE TOKEN EN LOS NUEVOS TOKENS QUE SE GENEREN POR EL SPLIT
// }

// Expands the env variables and $? of the 'commands' and split words if needed.
// Finally, performs quote removal and returns the result.
int expansor (t_general *data)
{
	t_token *token;
	t_xtkn	*xtkn;

	printf (GREEN"\n******************* EXPANSOR *******************\n"END);
	token = data->first_token;
	while (token)
	{
		xtkn = expand_xtkn(token, data->exit_status, data->env_lst, data);
		if (!xtkn)
		{
			//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
			return (0);
		}
		printf ("token expandido |%s|\n\n", xtkn->content);
		//split_xtkn (xtkn, data);
		token = token->next;
	}


	//Al acabar de crear todos los xtokens puedo liberar los tokens
	return (1);
}



