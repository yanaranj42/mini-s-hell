/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/09 21:40:46 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	preparations_for_the_executor(t_general *data)
{
	if (get_matrix_env(data, data->env_lst) == 0)
	{
		printf("Failure in matrix enviroment creation");
		data->exit_status = 1;
		return (0);
	}
	if (get_all_paths(data->env_lst, data) == 0)
		return (0);
	if (get_command(data, data->first_xtkn) == 0)
	{
		printf("Error: There have been problems creating commands");
		return (0);
	}
	free_xtkns_list(data);
	return (1);
}
