/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/29 20:03:35 by mfontser         ###   ########.fr       */
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

void put_new_list_xtoken_node (t_general *data, t_token *xtkn)
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



t_xtkn *token_to_xtoken(t_token *token)
{
	t_xtkn	*xtkn;

	xtkn = create_xtoken ()
	if (!xtkn)
		{
			//REVISAR MENSAJE DE ERROR, Y SI HAY QUE LIBERAR COSAS
			//CUIDADO NO HACER DOUBLE FREE
			return (0);
		}
	
	//relleno xtkn
	// xtkn->content_pre_expansion = ft_strdup(token->content);
	xtkn->content = '\0';
	xtkn->type = token->type;

	//ubico el nuevo cmd
	put_new_list_xtoken_node (data, xtkn);
	return(xtkn);
		
}


char	*adapted_strjoin(char *store, char *buffer) //LLEVAR A LIBFT
{
	char	*fusion;
	int		i;
	int		j;

	i = 0;
	if (store == NULL)
	{
		store = malloc (sizeof(char) * 1);
		if (!store)
			return (NULL);
		store[0] = '\0';
	}
	fusion = malloc (sizeof(char) * (ft_strlen(store) + ft_strlen(buffer) + 1));
	if (!fusion)
		return (killer_text(store));
	j = 0;
	while (store[i] != '\0')
		fusion[i++] = store[j++];
	j = 0;
	while (buffer[j] != '\0')
		fusion[i++] = buffer[j++];
	fusion[i] = '\0';
	free (store);
	return (fusion);
}

int check_expansor_variable_exists (char *tmp, t_ env *env)
{
	t_env *env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0))
			return (1);
		env_tmp = env_tmp->next;
	}

	return (0);
}

int change_expansor_variable(t_token *token, char *tmp, t_ env *env)
{
	t_env *env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0))
		{
			token->content = adapted_strjoin(token->content, env_tmp->value);
			if (!token->content)
			{
				//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
				return (0);
			}
		}
	}
	return(1);
}

int build_expanded_content (t_xtkn	*xtkn, t_token *token, int exit_status, t_ env *env, t_general *data)
{
	int i;
	char *tmp;

	i = 0;
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
					tmp = strjoinchar (tmp, token->content[i])
					if (!tmp)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
					i++;
				}
				if (data->qdata.miniquotes == 1)
				{
					account_quotes (token->content[i], data);
					token->content = adapted_strjoin(token->content, tmp);
					if (!token->content)
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
						if (token->content[i] == '?')
						{
							token->content = adapted_strjoin(token->content, exit_status);
							if (!token->content)
							{
								//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
								return (0);
							}
						}
						else 
						{
							token->content = adapted_strjoin(token->content, "");
							if (!token->content)
							{
								//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
								return (0);
							}
						}
					}
					else
					{
						if(change_expansor_variable(token,tmp, env) == 0)
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
						if (token->content[i] == '?')
						{
							token->content = adapted_strjoin(token->content, exit_status);
							if (!token->content)
							{
								//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
								return (0);
							}
						}
						else if (token->back->type == INPUT || token->next->type == INPUT || token->next->type == INPUT)
					}

				}
			}
			if (token->content[i] && ft_isdigit(token->content[i]) == 1)
			{

			}
			if (token->content[i] && token->content[i] == '"' && data->qdata.miniquotes == 0)
			{
				account_quotes (token->content[i], data);
			}
			if (token->content[i] && token->content[i] == '\'' && data->qdata.quotes == 0)
			{
				account_quotes (token->content[i], data);
			}
			if (token->content[i] && token->content[i] == '"' && data->qdata.miniquotes == 0 && && data->qdata.quotes == 1)
			{
				account_quotes (token->content[i], data);
			}
			if (token->content[i] && token->content[i] == '\'' && data->qdata.miniquotes == 1 && && data->qdata.quotes == 0)
			{
				account_quotes (token->content[i], data);
			}



			token->content = adapted_strjoin(token->content, tmp);
			if (!token->content)
			{
				//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
				return (0);
			}
		}


		i++;
	}
	return (1)
}

t_xtkn *expand(t_token *token, int exit_status, t_env *env, t_general *data)
{
	t_xtkn	*xtkn;

	xtkn = token_to_xtoken(token);
	if (build_expanded_content (xtkn, token, exit_status, env, data) == 0)
	{
		//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
		return (NULL);
	}


}



// Expands the env variables and $? of the 'commands' and split words if needed.
// Finally, performs quote removal and returns the result.
int expansor (t_general *data)
{
	t_token *token;
	t_xtkn	*xtkn;

	token = data->first_token;
	while (token)
	{
		xtkn = expand(token, data->exit_status, data->env_lst, data);
		if (!xtkn)
		{
			//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
			return (0);
		}
		token = token->next;
	}


	//Al acabar de crear todos los xtokens puedo liberar los tokens
	return (1);
}