/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:07:54 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/20 15:48:28 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	handle_args(t_general *data, char *argv)
{
	char	**arr;
	char	*name;

	printf ("entro2\n");
	if (!ft_strchr(argv, '='))
		data->equal = 0;
	else
		data->equal = 1;
	arr = ft_split(argv, '=');
	if (!export_opt(arr[0], argv)) //AQUI
	{
		printf ("exit status 2 %d\n", data->exit_status);
		return (error_opt(arr[0], arr[1], arr, argv));
	}
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
			add_upd_env(data, arr[0], arr[1]);
	}
	return (arr_clean(arr), 0);
}

int ft_export(t_general *data)
{
    t_env   *tmp_env;
    char    **argv;
    int     i;
    i = 1;
    printf ("entro\n");
    argv = data->first_cmd->argv;
    tmp_env = data->env_lst;
    if (!argv[1])
        print_export_lst(tmp_env);
    while (argv[i])
    {
        if (argv[i][0] == '=')
            error_opt("", "\'", NULL, argv[i]);
        else if (!data->exit_status)
        {
            data->exit_status = handle_args(data, argv[i]);
        	printf ("exit status 3 %d\n", data->exit_status);
        }
        else
            handle_args(data, argv[i]);
        i++;
    }
    if (data->env_matrix)
        data->env_matrix = arr_clean(data->env_matrix);
    get_matrix_env(data, data->env_lst);
    if (data->exit_status == 1)
    	return (1);
    return (0);
}
