/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:20:52 by yanaranj          #+#    #+#             */
/*   Updated: 2024/10/01 14:01:35 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/* Este builtin borra las variables de entorno que elijamos y modifica tambien
    la lista que tengamos en el env que se vean afectadas por esta. (ex. CD,
	OWD, OLDPWD...)
    *-Si la variabe no existe, no hace nada, elimina el resto de variables y
	vuelve al prompt
    
    --> puedo recibir + variables en la misma linea para eliminar

	argv[0] --> unset
	argv[1] --> variable
*/
/*
	no se esta moviendo correctamente la lista despues de eliminar la var eencontrada.
	mirar de hacerlo con iteradores
*/
/* void	do_unset(t_general *data, char *var)
{
	t_env	*tmp;
	t_env	*new_env;
	
	tmp = data->env_lst;
	new_env = NULL;
	while (tmp != NULL)
	{
		printf("env var: %s\tparam var: %s\n", tmp->name, var);
		if (ft_strncmp(tmp->name, var, ft_strlen(var)) == 0)
		{
			printf("env var: %s\tparam var: %s\n", tmp->name, var);
			printf("%s\t Hay match y procedo a eliminarla\n", var);
			data->env_lst = data->env_lst->next;
			unset_free(tmp);
			return ;
		}
		tmp = tmp->next;
	}
	printf("%s:\tMatch not found\n\n\n", var);
	printf("Si no es el final y no encuentro la var, copiamos esta en el nodo\n");
	printf("actual y nos movemos al siguiente\n");
	while (tmp != NULL && ft_strncmp(tmp->name, var, ft_strlen(var)) != 0)
	{
		new_env = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	new_env->next = tmp->next;
	unset_free(tmp);
}
int    ft_unset(t_general *data)
{
    t_env   *env;
    char	**argv;
	int		i;

	i = 1;
	argv = data->first_token->argv;
	env = data->env_lst;
	if (!argv[i])//variable name
		;
	while (argv[i])
	{
		printf("param recibido: %s\n", argv[i]);
		do_unset(data, argv[i]);
		i++;
	}
	if (data->env_matrix)
		arr_clean(data->env_matrix);
	printf("Aqui actualizamos la lst del env:\n");
	//get_matrix_env(data, data->env_lst);
	if (!data->env_matrix)
		return (error_brk(data, ERR01, NULL, 12));
	return (OK);
} */
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
	printf("he salid del do_unset\n\n");
	 
	return (OK);
}

