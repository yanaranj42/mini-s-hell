/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:05:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/06 23:48:46 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	parser(t_general *data)
{
	int		i;
	char	**argv;

	i = 0;
	argv = NULL;
	while (data->line[i])
	{
		if (prepare_pretoken(data, &i, &argv) == 0)
			return (0);
		if (build_tokens_list(data, &argv) == 0)
			return (0);
		free(data->pretoken);
		data->pretoken = NULL;
		free_pretoken_argv(&argv);
	}
	return (1);
}
