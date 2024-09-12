/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaja <yaja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:44:12 by yanaranj          #+#    #+#             */
/*   Updated: 2024/09/12 13:01:21 by yaja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/* Ya funciona cuando llamamos al export sin args. Es decir, llama a la lista
 * y la printa ordenada.
 * estoy con la parte de gestionar los args, por ahora tenemos el split del =
 * y su error en caso de que el argv que queremos añadir o modificar como var
 * de entorno este mal escrita. Check free.c
*/
int	handle_args(t_general *data, char *argv)
{
	char	**arr;
	char	*name;

	arr = ft_split(argv, '=');
	if (export_opt(arr[0]) == 0)
		return (error_opt(arr[0], arr[1], arr));//mensaje de error estilo bash
	else
	{
		if (ft_strchr(arr[0], '+'))
		{
			printf(RED"si hay +\n"END);
			name = ft_substr(arr[0], 0, ft_strchr(arr[0], '+') - arr[0]);
			if (!name)
				return (1);
			export_plus_var(data, name, arr[1]);
			free(name);
		}
		else
		{
			printf(RED"NO HAY +\n"END);
			printf("entro aqui para actualizar la variable de entorno\n");
			add_upd_env(data, arr[0], arr[1]);
		}
	}
	int i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	//arr = arr_clean(arr);*/
	return (0);
}
//para reducir linea, pasamos el argv como parametro desde pseudoexecurtor
//error de al hacer uso de arr_clean. Rehacer todas la funciones de handle args
int	ft_export(t_general *data)
{
	char	**argv;
	t_env	*tmp_env;
	int		err;
	int		i;

	err = 0;
	argv = data->first_token->argv;
	tmp_env = data->env_lst;
	i = 1;
	if (!argv[1])
		return (print_export_lst(tmp_env));
	while (argv[i])
	{
		if (!err)
		{
			err = handle_args(data, argv[i]);
			printf("%d\n", err);
		}
		else
			handle_args(data, argv[i]);
		i++;
	}
	/*if (data->env)//tenemos que borrar esta lista porque se ha agregado o modificado una var
		data->env = arr_clean(data->env);
	data->env = env_converter(data->env_lst);*/
	printf("%i\n", err);
	return (err);
}
