/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/27 19:19:54 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//Necesito la lista de tokens que tengo hasta ahora, el exit status hasta ahora y el env.

// Expandir las variables del comando 'cmd' (como una lista de tokens) y divide
// palabras si es necesario. Finalmente, realiza la eliminación de cotizaciones y devuelve el resultado.


t_token *token_to_xtoken(t_token *tkn_content)
{
	
}


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

t_token *expand(t_token *token, int exit_status, t_ env *env)
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
	xtkn->content_pre_expansion = ft_strdup(token->content);
	xtkn->content_post_expansion = '\0';
	xtkn->type = token->type;



	//ubico el nuevo cmd
	put_new_list_xtoken_node (data, xtkn);
		



	token_to_xtoken(tkn);
}



// Expands the env variables and $? of the 'commands' and split words if needed.
// Finally, performs quote removal and returns the result.
void expansor (t_general *data)
{
	t_token *token;

	token = data->first_token;
	while (token)
	{
		expand(token, data->exit_status, data->env_lst);
		token = token->next;
	}
}






	t_xtoken	xtok;
	char		*str;
	int			q_stat;
	int			char_stat;

	xtok.type = tok->type;
	xtok.val = NULL;
	q_stat = UNQUOTED;
	str = tok->val;
	while (*str)
	{
		char_stat = quote_stat(&q_stat, *str);
		xtok_addc(&xtok, *str, UNEXPANDED, char_stat);
		++str;
	}
	return (xtok);



exp_toke = expand(cmd, exit_status, env);


t_list	**expand_and_split(t_list **commands, int exit_status, char **env);