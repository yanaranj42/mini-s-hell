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


int expand_final_value (t_xtkn *xtkn, t_env *env_tmp, int *i)
{
	if (env_tmp->value[*i] == '"')
	{
		xtkn->content = strjoinchar (xtkn->content, 30); //Cambio las quotes por un valor no imprimible antes de expandir. Asi no tendre problemas al gestionar el split y saber que comillas quitar
		if (!xtkn->content)
			return (0);
	}
	else if (env_tmp->value[*i] == '\'')
	{
		xtkn->content = strjoinchar (xtkn->content, 31); //Cambio las miniquotes por un valor no imprimible antes de expandir. Asi no tendre problemas al gestionar el split y saber que comillas quitar
		if (!xtkn->content)
			return (0);
	}
	else 
	{
		xtkn->content = strjoinchar (xtkn->content, env_tmp->value[*i]);
		if (!xtkn->content)
			return (0);
	}
	return(1);
}



int change_expansor_variable(t_xtkn *xtkn, char *tmp, t_env *env)
{
	t_env *env_tmp;
	int i;

	i = 0;
	env_tmp = env;
	if (!tmp)
		return (0);
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0))
		{
			while (env_tmp->value[i])
			{
				if (expand_final_value (xtkn, env_tmp, &i) == 0)
					return(0);
				i++;
			}
		}
		env_tmp = env_tmp->next;
	}
	return(1);
}



char *identify_variable_to_expand (t_token *token, int *i)
{
	char *tmp;
	tmp = NULL; //IMPORTANTISIMO inicializar, sino la primera vez que hago el strjoinchar coge un valor random y no funciona bien.

	while (token->content[*i] && (ft_isalpha(token->content[*i]) == 1 || ft_isdigit(token->content[*i]) == 1 || token->content[*i] == '_'))
	{
		tmp = strjoinchar (tmp, token->content[*i]);
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

int build_heredoc_delimiter (t_xtkn	*xtkn, char *tmp)
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
	return (1);
}

int manage_quotes_variable (t_xtkn	*xtkn, char *tmp, t_env *env)
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
	return (1);		
}


int quotes_conversion (t_xtkn	*xtkn, char *tmp, t_env *env)
{
	if (xtkn->back && xtkn->back->type == HEREDOC) // Si antes tiene un heredoc quiere decir que es un limitador y no se tiene que expandir
	{
		if (build_heredoc_delimiter (xtkn, tmp) == 0)
			return (0);
	}
	else
	{
		if (manage_quotes_variable (xtkn,tmp, env) == 0)
			return (0);
	}
	return (1);	
}


int manage_inexistent_regular_variable (t_xtkn	*xtkn, t_token *token, char *tmp, int *i)
{
	//si hay un $nada y luego cosas, no entra y simplemente no se mete nada en content. Si lo siguiente es un $nada y ya no hay nada mas, entonces metera de golpe los dos $nada juntos en el contenido. Si en cambio despues de este segundo hay algo mas, simplemente saltara y se metera unicamente lo que hay a continuacion
	if (!xtkn->content && !token->content[*i] && token->back && (token->back->type == INPUT || token->back->type == OUTPUT || token->back->type == APPEND))
	{
		xtkn->content = ft_strdup (token->content);
		if (!xtkn->content)
		{
			free(tmp);
			tmp = NULL;
			return (0);
		}
	}
	return (1);
}


int manage_regular_variable (t_xtkn	*xtkn, t_token *token, char *tmp, t_env *env)
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
	return (1);
}



int regular_conversion (t_token *token, t_xtkn	*xtkn, char *tmp, t_env *env, int *i)
{

	if (xtkn->back && xtkn->back->type == HEREDOC) // Si antes tiene un heredoc quiere decir que es un limitador y no se tiene que expandir
	{
		
		if (build_heredoc_delimiter (xtkn, tmp) == 0)
			return (0);
	}
	else
	{
		if (check_expansor_variable_exists (tmp, env) == 0)
		{
			if (manage_inexistent_regular_variable (xtkn, token, tmp, i) == 0)
			return (0);
		}
		else
		{
			if (manage_regular_variable (xtkn, token, tmp, env) == 0)
				return (0);
		}
			
	}
	return (1);
}	


int expand_regular_variable(t_token *token, t_xtkn	*xtkn,  t_env *env, int * i, t_general *data)
{
	char *tmp;

	tmp = identify_variable_to_expand(token, i);
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
		if (regular_conversion (token, xtkn, tmp, env, i) == 0)
			return (0);
	}
	free(tmp);
	tmp = NULL;
	return (1);
}


int expand_exit_status_variable (t_xtkn	*xtkn, int exit_status, int *i)
{
	char *exit_number;

	exit_number = ft_itoa (exit_status);
	if (!exit_number)
		return (0);
	xtkn->content = adapted_strjoin(xtkn->content, exit_number);
	if (!xtkn->content)
	{
		free (exit_number);
		return (0);
	}
	free (exit_number);
	(*i)++;
	return (1);
}


int expand_digit_variable (t_general *data, t_token *token, t_xtkn	*xtkn, int *i)
{
	if (data->qdata.miniquotes == 1)
	{
		xtkn->content = strjoinchar (xtkn->content, '$');
		if (!xtkn->content)
			return (0);
		xtkn->content = strjoinchar (xtkn->content, token->content[*i]);
		if (!xtkn->content)
			return (0);
	}
	else 
	{
		if (token->content[*i] == '0')
		{
			xtkn->content = adapted_strjoin(xtkn->content, "✌️ bash");
			if (!xtkn->content)
				return (0);
		}
		else 
		{
			xtkn->content = adapted_strjoin(xtkn->content, "");
			if (!xtkn->content)
				return (0);	
		}
	}
	(*i)++;
	return (1);
}


int manage_quotes_after_dollar (t_general *data, t_token *token, t_xtkn	*xtkn, int *i)
{
	account_quotes (token->content[*i], data);
	xtkn->content = strjoinchar (xtkn->content, token->content[*i]);
	if (!xtkn->content)
		return (0);
	(*i)++;
	return (1);
}


int manage_miniquotes_after_dollar (t_general *data, t_token *token, t_xtkn	*xtkn, int *i)
{
	account_quotes (token->content[*i], data);
	xtkn->content = strjoinchar (xtkn->content, token->content[*i]);
	if (!xtkn->content)
		return (0);
	(*i)++;
	return (1);
}


int manage_dollar_variable_between_quotes (t_general *data, t_token *token, t_xtkn	*xtkn, int *i)
{
	account_quotes (token->content[*i], data);
	xtkn->content = strjoinchar (xtkn->content, '$');
	if (!xtkn->content)
		return (0);
	xtkn->content = strjoinchar (xtkn->content, token->content[*i]);
	if (!xtkn->content)
		return (0);
	(*i)++;
	return (1);
}

int there_is_expansion_to_manage_2 (t_xtkn *xtkn, t_token *token, int * i, t_general *data)
{
	if (token->content[*i] && token->content[*i] == '"' && data->qdata.miniquotes == 0 && data->qdata.quotes == 0)
	{
		if (manage_quotes_after_dollar (data, token, xtkn, i) == 0)
			return (0);
	}
	else if (token->content[*i] && token->content[*i] == '\'' && data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
	{
		if (manage_miniquotes_after_dollar (data, token, xtkn, i) == 0)
			return (0);
	}
	else if (token->content[*i] && (token->content[*i] == '"' || token->content[*i] == '\''))
	{
		if (manage_dollar_variable_between_quotes (data, token, xtkn, i) == 0)
			return (0);
	}
	
	return (1);
}


int there_is_expansion_to_manage (t_xtkn *xtkn, t_token *token, t_env *env, int * i, t_general *data)
{
	if (token->content[*i] && (ft_isalpha(token->content[*i]) == 1 || token->content[*i] == '_'))
	{
		if (expand_regular_variable (token, xtkn, env, i, data) == 0)
			return (0);
	}
	else if (token->content[*i] && token->content[*i] == '?')
	{
		if (expand_exit_status_variable(xtkn, data->exit_status, i) == 0)
			return (0);
	}
	else if (token->content[*i] && ft_isdigit(token->content[*i]) == 1)
	{
		if (expand_digit_variable (data, token, xtkn, i) == 0)
			return (0);
	}
	else
	{
		if (there_is_expansion_to_manage_2 (xtkn, token, i, data) == 0)
			return (0);
	}
	return (1);	
}

int build_expanded_content (t_xtkn	*xtkn, t_token *token, t_env *env, t_general *data)
{
	int i;
	
	printf ("\n🟠 Toquen \n"); //BORRAR
	printf("\n# Expandir contenido del token |%s|\n", token->content);
	i = 0;
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
			if (there_is_expansion_to_manage (xtkn, token, env, &i, data) == 0)
				return (0);
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



t_xtkn *expand_xtkn(t_token *token, t_env *env, t_general *data)
{
	t_xtkn	*xtkn;

	xtkn = token_to_xtoken(token, data);
	if (!xtkn)
	{
		printf("Error: There have been problems creating expanded tokens\n");
		return (NULL);
	}
	if (build_expanded_content (xtkn, token, env, data) == 0)
	{
		printf("Error: There have been problems building the content of the expanded tokens\n");
		return (NULL);
	}
	return (xtkn);
}