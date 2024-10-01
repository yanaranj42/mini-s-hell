/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:07:54 by yanaranj          #+#    #+#             */
/*   Updated: 2024/09/29 16:15:38 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	handle_args(t_general *data, char *argv)
{
	char	**arr;
	char	*name;

	if (!ft_strchr(argv, '='))
		data->equal = KO;
	else
		data->equal = OK;
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
	data->ret_exit = 0;
	argv = data->first_token->argv;
	tmp_env = data->env_lst;
	/*printf(YELLOW"INICIO EXPORT Y 1o PRINTO LA LISTA ENV\n"END);
	while (tmp_env)
	{
		printf("%s=%s\n", tmp_env->name, tmp_env->value);
		tmp_env = tmp_env->next;
	}*/
	if (!argv[1])
		print_export_lst(data, tmp_env);//add data para la estructura y flag equal
	while (argv[i])
	{
		if (argv[i][0] == '=')
			error_opt("", "\'", NULL, argv[i]);
		else if (!data->ret_exit)
			data->ret_exit = handle_args(data, argv[i]);//el argv puede ser: LOG+=hola//LOG//LOG=//LOG$
		else
			handle_args(data, argv[i]);
		i++;
	}
	return (data->ret_exit);//este return sirve para cuando se hace echo $?
}
