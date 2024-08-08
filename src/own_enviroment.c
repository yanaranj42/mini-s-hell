/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_enviroment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:54:46 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/08 14:11:33 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int env_matrix_base (char **env)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (env[i] != NULL)
	{
		count++;
		i++;
	}
	return (count);
}

int	get_own_env(char **env, t_general *data)
{
	int	i;

	i = 0;

	if (env && env[i]) //miro que exista env y luego entro a mirar si existe la columna
	{
		data->own_env = malloc (sizeof(char*) * (env_matrix_base(env) + 1));
		if (!data->own_env)
		{
			perror_message(NULL, "Failure in enviroment creation");
			return (0);
		}
		while (env[i] != NULL)
		{
			data->own_env[i] = ft_strdup(env[i]);
			if (data->own_env[i] == NULL)
			{
				perror_message(NULL, "Malloc failure in take enviroment");
				free_env(data);
				return (0);
			}
			i++;
		}
		data->own_env[i] = NULL;
	}
	//borrar:
	printf("*********Own enviroment*********\n");
	print_env(data);
	printf("\n");
	return (1);
}
