/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:07:54 by yanaranj          #+#    #+#             */
/*   Updated: 2024/10/10 11:36:57 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
			add_upd_env(data, arr[0], arr[1]);
	}
	return (arr_clean(arr), 0);
}

int	ft_export(t_general *data)
{
	t_env	*tmp_env;
	char	**argv;
	int		i;
	
	i = 1;
	data->exit_status = 0;
	argv = data->first_cmd->argv;
	tmp_env = data->env_lst;
	if (!argv[1])
		print_export_lst(data, tmp_env);//add data para la estructura y flag equal
	while (argv[i])
	{
		if (argv[i][0] == '=')
			error_opt("", "\'", NULL, argv[i]);
		else if (!data->exit_status)
			data->exit_status = handle_args(data, argv[i]);//el argv puede ser: LOG+=hola//LOG//LOG=//LOG$
		else
			handle_args(data, argv[i]);
		i++;
	}
	return (data->exit_status);//este return sirve para cuando se hace echo $?
}