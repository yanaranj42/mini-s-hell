/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:07:54 by yanaranj          #+#    #+#             */
/*   Updated: 2024/09/17 15:42:26 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*	split: si no encuentra el char limitador, genera igualmente el array, pero
	de un valor.
	Primero comprobamos que tenemos bien escrita la variable que queremos
	modificar o crear. Si hay algo mal, salimos con el msj de bash.
	Si funciona, comprobamos si tenemos un +. Si es asi, hacemos un export segun
	ese caso.
	Si no tenemos el +, 
*/
int	handle_args(t_general *data, char *argv)
{
	char	**arr;
	char	*name;
	if (!ft_strchr(argv, '='))
		data->equal = KO;
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
	arr_clean(arr);
	return (0);
}

void	ft_export(t_general *data)
{
	t_env	*tmp_env;
	char	**argv;
	int		i;
	
	i = 1;
	data->ret_exit = 0;
	argv = data->first_token->argv;
	tmp_env = data->env_lst;
	if (!argv[1])
		print_export_lst(data, tmp_env);//add data para la estructura y flag equal
	while (argv[i])
	{
		if (!data->ret_exit)
			data->ret_exit = handle_args(data, argv[i]);//el argv puede ser: LOG+=hola//LOG//LOG=//LOG$
		else
			handle_args(data, argv[i]);
		i++;
	}
	printf("%i\n", data->ret_exit);
	//return (data->ret_exit);//este return sirve para cuando se hace echo $?
}