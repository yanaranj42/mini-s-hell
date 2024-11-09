/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/04 03:13:26 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void put_new_list_cmd_node (t_general *data, t_cmd *new_cmd)
{
	t_cmd  *tmp_cmd;

	if (!data->first_cmd)
	{
		data->first_cmd = new_cmd;
		data->first_cmd->next = NULL;
	}
	else
	{
		tmp_cmd = data->first_cmd;
		while (tmp_cmd && tmp_cmd->next)
			tmp_cmd = tmp_cmd->next;
		tmp_cmd->next = new_cmd;
		new_cmd->next = NULL;
	}
}

t_cmd *create_command (void)
{
	t_cmd 	*new_cmd;

	new_cmd = malloc (sizeof(t_cmd) * 1);
	if (!new_cmd)
		return (NULL);
	return (new_cmd);

}

t_cmd *create_and_put_new_cmd_node (t_general *data)
{
	t_cmd 	*new_cmd;

		new_cmd = create_command ();
		if (!new_cmd)
		{
			free_get_cmd_process(data);
			return (NULL);
		}
		put_new_list_cmd_node (data, new_cmd);
		return (new_cmd);
}
