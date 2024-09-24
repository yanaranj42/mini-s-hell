/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/24 18:34:19 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Necesito la lista de tokens que tengo hasta ahora, el exit status hasta ahora y el env.

// Expandir las variables del comando 'cmd' (como una lista de tokens) y divide
// palabras si es necesario. Finalmente, realiza la eliminación de cotizaciones y devuelve el resultado.




t_token *expand(t_token *first_token, int exit_status, t_ env *env)
{
	t_token	*xtoken;


	xtoken = token_to_xtoken((t_token *)node->val);

}

void expansor (t_general *data)
{
	t_token	*new_cmd;
	t_token	*exp_token;

	exp_token = expand(data->first_token, data->exit_status, data->env_lst);
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