/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_enviroment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:54:46 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/09 14:29:44 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
/*
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
*/
int	get_own_env(t_general *data, char **env)
{
	t_env	s_env;
	int		i;

	i = 0;

	while (env[i] != NULL)
	{
		s_env = malloc(sizeof(t_env));
		if (!s_env)
			return (perror_message(NULL, "Fail in env creation"), 0);
		s_env->name = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		s_env->value = ft_strdup(getenv(s_env->name));
		s_env->next = NULL;
	}
	//borrar:
	printf("*********Own enviroment*********\n");
	print_env(data);
	printf("\n");
	return (1);
}
