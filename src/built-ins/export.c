/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaja <yaja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:44:12 by yanaranj          #+#    #+#             */
/*   Updated: 2024/09/02 14:59:55 by yaja             ###   ########.fr       */
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
	char	**av_arr;
	//char	*name;
	(void)data;
	av_arr = ft_split(argv, '=');
	if (!export_opt(av_arr[0]))
		return (error_opt(av_arr[0], av_arr[1], av_arr));
	return (OK);
}
int	ft_export(t_general *data)
{
	char	**argv; //cmd
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
			handle_args(data, argv[i]);
		else
			handle_args(data, argv[i]);
		i++;
	}
	return (0);
}
