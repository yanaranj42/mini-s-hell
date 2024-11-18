/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:07:54 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/07 18:12:43 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
/* TENGO QUE PONER UNA FLAG PARA QUE NO PRINTE LAS NUEVAS VARIABLES QUE NO TENGAN VALOR
ES DECIR, SI HAGO export a. Esta no se debe printar en el env y printar sin  = en el 
export. Creo que ahora ya funcionaria.
Esto haria que volvamos a cambiar a la version original el:
int	fill_matrix(t_env *tmp, t_general *data, int *i)
*/
int	handle_args(t_general *data, char *argv)
{
	char	**arr;
	char	*name;

	if (!ft_strchr(argv, '='))
		data->equal = 0;
	else
		data->equal = 1;
	arr = ft_split(argv, '=');
	if (!export_opt(arr[0], argv))
		return (error_opt(arr[0], arr[1], arr, argv));
	else
	{
		if (ft_strchr(arr[0], '+'))
		{
			name = ft_substr(arr[0], 0, ft_strchr(arr[0], '+') - arr[0]);
			if (!name)
				return (arr_clean(arr), 1);
			export_plus_var(data, name, arr[1]);
			free(name);
		}
		else
		{
			//printf("name: %s - value: [%s]\n", arr[0], arr[1]);//BORRAR
			add_upd_env(data, arr[0], arr[1]);
		}
	}
	return (arr_clean(arr), 0);
}

int	ft_export(t_general *data)
{
	t_env	*tmp_env;
	char	**argv;
	int		i;

	i = 1;
	data->exit_status = 0; // PORQUE???
	argv = data->first_cmd->argv;
	tmp_env = data->env_lst;
	int j = 0;
	for (; data->env_lst != NULL; j++) {
		data->env_lst = data->env_lst->next; //MODIFICAR!!!!
	}
	data->env_lst = tmp_env;
	printf("LIST size : %d\n", j);
	if (!argv[1])
		print_export_lst(tmp_env, data);
	while (argv[i])
	{
		if (argv[i][0] == '=')
			error_opt("", "\'", NULL, argv[i]);
		else if (!data->exit_status)
			data->exit_status = handle_args(data, argv[i]);
		else
			handle_args(data, argv[i]);
		i++;
	}
	if (data->env_matrix)
		data->env_matrix = arr_clean(data->env_matrix);
	printf("Flag1\n");
	get_matrix_env(data, data->env_lst);
	tmp_env = data->env_lst;
	j = 0;
	for (; data->env_lst != NULL; j++) {
		data->env_lst = data->env_lst->next;
	}
	data->env_lst = tmp_env;
	printf("LIST size AFTER : %d\n", j);
	printf("Flag2\n");
	return (0);
}
