/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaja <yaja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:20:52 by yanaranj          #+#    #+#             */
/*   Updated: 2024/10/04 11:52:37 by yaja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//SEGUNDA VERSION

void	do_unset(t_general *data, char *var)
{
	t_env	*tmp;//
	t_env	*head;//tiene la ref al inicio de la lista y se  va modificando
	
	head = data->env_lst;
	tmp = NULL;
	if (ft_strncmp(head->name, var, ft_strlen(var)) == 0)
	{
		printf("Match found: %s - %s", head->name, var);
		data->env_lst = data->env_lst->next;
		unset_free(head);
		return ;
	}
	while (head != NULL && ft_strncmp(head->name, var, ft_strlen(var)) != 0)
	{
		tmp = head;
		head = head->next;
	}
	if (head == NULL)
		return ;
	tmp->next = head->next;
	unset_free(head);
}
//recibira los args desde el fist_cmd
int	ft_unset(t_general *data)
{
	t_env	*head;
	char	**argv;
	int		i;

	i = 1;
	argv = data->first_token->argv;
	head = data->env_lst;
	if (!argv[i])
		;
	while (argv[i])
	{
		do_unset(data, argv[i]);
		i++;
	}
	if (data->env_matrix)
		arr_clean(data->env_matrix);
	get_matrix_env(data, head);
	return (OK);
}

