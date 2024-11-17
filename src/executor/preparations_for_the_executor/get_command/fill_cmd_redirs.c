/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/11 12:43:39 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	fill_redir_node(t_general *data, t_xtkn **tmp_xtkn, t_redir *new_redir)
{
	new_redir->type = (*tmp_xtkn)->type;
	new_redir->file_name = ft_strdup((*tmp_xtkn)->next->content);
	if (!new_redir->file_name)
	{
		free_get_cmd_process(data);
		return (0);
	}
	new_redir->heardoc_expansion = (*tmp_xtkn)->next->heardoc_expansion;
	*tmp_xtkn = (*tmp_xtkn)->next;
	return (1);
}

void	put_new_list_redir_node(t_cmd *new_cmd, t_redir *new_redir)
{
	t_redir	*tmp_redir;

	if (!new_cmd->first_redir)
	{
		new_cmd->first_redir = new_redir;
		new_cmd->first_redir->next = NULL;
	}
	else
	{
		tmp_redir = new_cmd->first_redir;
		while (tmp_redir && tmp_redir->next)
			tmp_redir = tmp_redir->next;
		tmp_redir->next = new_redir;
		new_redir->next = NULL;
	}
}

t_redir	*create_redir(void)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir) * 1);
	if (!new_redir)
		return (NULL);
	return (new_redir);
}

t_redir	*create_and_put_new_redir_node(t_general *data, t_cmd *new_cmd)
{
	t_redir	*new_redir;

	new_redir = create_redir();
	if (!new_redir)
	{
		free_get_cmd_process(data);
		return (NULL);
	}
	put_new_list_redir_node(new_cmd, new_redir);
	return (new_redir);
}
