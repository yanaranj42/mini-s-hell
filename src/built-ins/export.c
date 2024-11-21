/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:07:54 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/21 14:25:38 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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
		return (error_identifier(arr[0], arr[1], arr, argv));
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

int	ft_export(char **argv, t_general *data)
{
	t_env	*tmp_env;
	int		i;

	i = 1;
	tmp_env = data->env_lst;
	if (!argv[1])
		return (print_export_lst(tmp_env));
	while (argv[i])
	{
		if (argv[i][0] == '-')
			return (data->exit_status = error_opt("export", argv[i][1]));
		if (argv[i][0] == '=')
			data->exit_status = error_identifier("", "\'", NULL, argv[i]);
		else if (!data->exit_status)
			data->exit_status = handle_args(data, argv[i]);
		else
			handle_args(data, argv[i]);
		i++;
	}
	if (data->env_matrix)
		arr_clean(data->env_matrix);
	get_matrix_env(data, data->env_lst);
	return (0);
}
