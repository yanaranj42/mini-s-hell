/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_argvs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/11 12:43:03 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	fill_cmd_argvs(int *i, t_cmd *new_cmd, t_xtkn **tmp_xtkn, t_general *data)
{
	new_cmd->argv[*i] = ft_strdup((*tmp_xtkn)->content);
	if (!new_cmd->argv[*i])
	{
		free_get_cmd_process(data);
		return (0);
	}
	(*i)++;
	return (1);
}

int	fill_cmd_argvs_and_redirs(t_general *data, t_xtkn **tmp_xtkn,
		t_cmd *new_cmd)
{
	int		i;
	t_redir	*new_redir;

	new_cmd->first_redir = NULL;
	i = 0;
	while (*tmp_xtkn && (*tmp_xtkn)->type != PIPE)
	{
		if (*tmp_xtkn && (*tmp_xtkn)->type == CMD_ARGV)
		{
			if (fill_cmd_argvs(&i, new_cmd, tmp_xtkn, data) == 0)
				return (0);
		}
		else
		{
			new_redir = create_and_put_new_redir_node(data, new_cmd);
			if (!new_redir)
				return (0);
			if (fill_redir_node(data, tmp_xtkn, new_redir) == 0)
				return (0);
		}
		if (*tmp_xtkn)
			*tmp_xtkn = (*tmp_xtkn)->next;
	}
	new_cmd->argv[i] = NULL;
	return (1);
}
