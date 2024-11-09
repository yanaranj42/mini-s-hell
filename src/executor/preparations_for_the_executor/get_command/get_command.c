/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/04 03:13:26 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


void get_next_cmd (t_xtkn **count_xtkn, t_xtkn **tmp_xtkn)
{
	if (*count_xtkn) 
		*count_xtkn = (*count_xtkn)->next;
	if (*tmp_xtkn)
		*tmp_xtkn = (*tmp_xtkn)->next;
}

int get_command (t_general *data, t_xtkn	*first_xtkn)
{
	t_xtkn *count_xtkn;
	t_xtkn *tmp_xtkn;
	t_cmd 	*new_cmd;
	int  	count;

	count_xtkn = first_xtkn;
	tmp_xtkn = first_xtkn;
	while (tmp_xtkn)
	{
		new_cmd = create_and_put_new_cmd_node (data);
		if (!new_cmd)
			return (0);
		count = count_cmd_argvs (&count_xtkn);
		new_cmd->argv = malloc (sizeof (char *) * (count + 1));
		if (!new_cmd->argv) 
		{
			free_get_cmd_process(data);
			return (0);
		}
		if (fill_cmd_argvs_and_redirs (data, &tmp_xtkn, new_cmd) == 0)
			return (0);
		get_next_cmd (&count_xtkn, &tmp_xtkn);
	}
	return (1);
}
