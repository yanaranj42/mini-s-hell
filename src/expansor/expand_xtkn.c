/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_xtkn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/25 03:22:22 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
						return (0);
				}
				else if (env_tmp->value[i] == '\'')
				{
					xtkn->content = strjoinchar (xtkn->content, 31); //Cambio las miniquotes por un valor no imprimible antes de expandir. Asi no tendre problemas al gestionar el split y saber que comillas quitar
					if (!xtkn->content)
						return (0);
				}
				else 
				{
					xtkn->content = strjoinchar (xtkn->content, env_tmp->value[i]);
					if (!xtkn->content)
						return (0);
				}
				i++;
			}
		}
		env_tmp = env_tmp->next;
	}
	return(1);
}



char *identify_variable_to_expand (char  c, int *i)
{
	char *tmp;
	tmp = NULL;

	while (c && (ft_isalpha(c) == 1 || ft_isdigit(c) == 1 || c == '_'))
	{
		tmp = strjoinchar (tmp, c);
		if (!tmp)
			return (NULL);
		(*i)++;
	}
	printf ("  Contenido del xtkn después del $: |%s|\n", tmp);
	return (tmp);
}

int miniquotes_conversion (t_xtkn	*xtkn, char *tmp)
{
	xtkn->content = adapted_strjoin(xtkn->content, tmp);
	if (!xtkn->content)
	{
		free(tmp);
		tmp = NULL;
		return (0);
	}
	return (1);
}


int quotes_conversion (t_xtkn	*xtkn, char *tmp, t_env *env)
{
	if (xtkn->back && xtkn->back->type == HEREDOC) // Si antes tiene un heredoc quiere decir que es un limitador y no se tiene que expandir
	{
		xtkn->content = strjoinchar (xtkn->content, '$');
		if (!xtkn->content)
		{
			free(tmp);
			tmp = NULL;
			return (0);
		}
		xtkn->content = adapted_strjoin(xtkn->content, tmp);
		if (!xtkn->content)
		{
			free(tmp);
			tmp = NULL;
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
				free(tmp);
				tmp = NULL;
				return (0);
			}
		}
		else
		{
			if (change_expansor_variable(xtkn,tmp, env) == 0)
			{
				free(tmp);
				tmp = NULL;
				return (0);
			}
		}	
	}
	return (1);	
}


int regular_conversion (t_token *token, t_xtkn	*xtkn, char *tmp, t_env *env, char c)
{

	if (xtkn->back && xtkn->back->type == HEREDOC) // Si antes tiene un heredoc quiere decir que es un limitador y no se tiene que expandir
	{
		xtkn->content = strjoinchar (xtkn->content, '$'); 
		if (!xtkn->content)
		{
			free(tmp);
			tmp = NULL;
			return (0);
		}
		xtkn->content = adapted_strjoin(xtkn->content, tmp);
		if (!xtkn->content)
		{
			free(tmp);
			tmp = NULL;
			return (0);
		}
	}
	else
	{
		if (check_expansor_variable_exists (tmp, env) == 0)
		{
			//si hay un $nada y luego cosas, no entra y simplemente no se mete nada en content. Si lo siguiente es un $nada y ya no hay nada mas, entonces metera de golpe los dos $nada juntos en el contenido. Si en cambio despues de este segundo hay algo mas, simplemente saltara y se metera unicamente lo que hay a continuacion
			if (!xtkn->content && !c && token->back && (token->back->type == INPUT || token->back->type == OUTPUT || token->back->type == APPEND))
			{
				xtkn->content = ft_strdup (token->content);
				if (!xtkn->content)
				{
					free(tmp);
					tmp = NULL;
					return (0);
				}
			}
		}
		else
		{
			if (expansor_variable_has_space(tmp, env) && xtkn->type == FILE_REDIRECTION)
			{
				xtkn->content = ft_strdup (token->content);
				if (!xtkn->content)
				{
					free(tmp);
					tmp = NULL;
					return (0);
				}
			}
			else if (change_expansor_variable(xtkn,tmp, env) == 0)
			{
				free(tmp);
				tmp = NULL;
				return (0);
			}
		}
	}
	return (1);
}	

expand_exit_status_variable ()
{
	exit_number = ft_itoa (exit_status);
	if (!exit_number)
	{
		free(tmp);
		tmp = NULL;
		return (0);
	}
	xtkn->content = adapted_strjoin(xtkn->content, exit_number);
	if (!xtkn->content)
	{
		free(tmp);
		tmp = NULL;
		free (exit_number);
		return (0);
	}
	free (exit_number);
	i++;
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
				tmp = identify_variable_to_expand(token->content[i], &i);
				if (!tmp)
					return (0);

				if (data->qdata.miniquotes == 1)
				{
					if (miniquotes_conversion (xtkn, tmp) == 0)
						return (0);
				}
				else if (data->qdata.quotes == 1)
				{
					if (quotes_conversion (xtkn, tmp, env) == 0)
						return (0);
				}
				else
				{
					if (regular_conversion (token, xtkn, tmp, env, token->content[i]) == 0)
						return (0);
				}
			}
			else if (token->content[i] && token->content[i] == '?')
			{
				exit_status_variable()
			}
			else if (token->content[i] && ft_isdigit(token->content[i]) == 1)
			{
				if (data->qdata.miniquotes == 1)
				{
					xtkn->content = strjoinchar (xtkn->content, '$');
					if (!xtkn->content)
					{
						free(tmp);
						tmp = NULL;
						return (0);
					}
					xtkn->content = strjoinchar (xtkn->content, token->content[i]);
					if (!xtkn->content)
					{
						free(tmp);
						tmp = NULL;
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
							free(tmp);
							tmp = NULL;
							return (0);
						}
						i++;
					}
					else 
					{
						xtkn->content = adapted_strjoin(xtkn->content, "");
						if (!xtkn->content)
						{
							free(tmp);
							tmp = NULL;
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
				if (!xtkn->content)
				{
					free(tmp);
					tmp = NULL;
					return (0);
				}
				i++;

			}
			else if (token->content[i] && token->content[i] == '\'' && data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
			{
				account_quotes (token->content[i], data);
				xtkn->content = strjoinchar (xtkn->content, token->content[i]);
				if (!xtkn->content)
				{
					free(tmp);
					tmp = NULL;
					return (0);
				}
				i++;
			}
			else if (token->content[i] && (token->content[i] == '"' || token->content[i] == '\''))
			{
				account_quotes (token->content[i], data);
				xtkn->content = strjoinchar (xtkn->content, '$');
				if (!xtkn->content)
				{
					free(tmp);
					tmp = NULL;
					return (0);
				}
				xtkn->content = strjoinchar (xtkn->content, token->content[i]);
				if (!xtkn->content)
				{
					free(tmp);
					tmp = NULL;
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
			return (0);
		i++;
	}
	printf("  Hay que expandir en heredoc?: %d\n", xtkn->heardoc_expansion);
	return (1);
}


t_xtkn *create_xtoken (void) //(t_general *data) SEGURAMENTE PARA ALGUN FREE
{
	t_xtkn 	*tmp_xtkn;

	tmp_xtkn = malloc (sizeof(t_xtkn) * 1);
	if (!tmp_xtkn)
		return (NULL);
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
		return (0);
	//relleno xtkn
	xtkn->content = NULL;
	xtkn->type = token->type;


	//ubico el nuevo cmd
	put_new_list_xtoken_node (data, xtkn);
	return(xtkn);
		
}






t_xtkn *expand_xtkn(t_token *token, int exit_status, t_env *env, t_general *data)
{
	t_xtkn	*xtkn;

	xtkn = token_to_xtoken(token, data);
	if (!xtkn)
	{
		printf("Error: There have been problems creating expanded tokens\n");
		return (NULL);
	}
	if (build_expanded_content (xtkn, token, exit_status, env, data) == 0)
	{
		printf("Error: There have been problems building the content of the expanded tokens\n");
		return (NULL);
	}
	return (xtkn);
}