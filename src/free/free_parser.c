/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 04:16:59 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 06:41:14 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_pretoken_argv(char ***argv)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = *argv;
	while (tmp && tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	tmp = NULL;
}

void	free_tokens_list(t_general *data)
{
	t_token	*tmp_token;

	while (data->first_token)
	{
		tmp_token = data->first_token->next;
		free(data->first_token->content);
		free(data->first_token);
		data->first_token = NULL;
		data->first_token = tmp_token;
	}
}

void	free_parsing_process(t_general *data, char ***argv)
{
	free(data->pretoken);
	data->pretoken = NULL;
	free_pretoken_argv(argv);
	free_tokens_list(data);
	data->exit_status = 1;
}
