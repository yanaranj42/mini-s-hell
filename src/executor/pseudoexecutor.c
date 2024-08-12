/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudoexecutor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 01:50:35 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/12 16:06:38 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//este pseudoexecutor va a recibir el data, mirara el argv[0] del token, va a comprobar si ese argv[0] se corresponde a un builtin y entonces va a llamar a la funcion execute builtin que va a llamar al builtin que le toca. 
//si llamo a env que llame al builtin env
//si llamo a exit que llame al builtin exit en vez de hacer el parche que tenemos de momento
//el executor llamara a los builins como si fueran comandos, pero en vez de hacer un execve, los llama directamente

//luego ampliaremos, ahora es para empezar a jugar con los builtins
//el pseudo executor en el futuro iterara sobre los tokens, y abrira pipes y redirecciones si toca, luego mirara el comando a ejecutar y lo ejecutara (executor builtin, executor cmd), y luego cerrara redirecciones y pipes si tiene que hacerlo


int pseudoexecutor(t_general *data)
{
	int i;

	i = 0; 
	if (ft_strncmp("echo", data->first_token->argv[0], 4) == 0)
		return (1);
	else if (ft_strncmp("cd", data->first_token->argv[0], 2) == 0)
		return (2);
	else if (ft_strncmp("pwd", data->first_token->argv[0], 3) == 0)
		ft_pwd();
	else if (ft_strncmp("export", data->first_token->argv[0], 6) == 0)
		return (4);
	else if (ft_strncmp("unset", data->first_token->argv[0], 5) == 0)
		return (5);
	else if (ft_strncmp("env", data->first_token->argv[0], 3) == 0)
		ft_env(data->env_lst);
	else if (ft_strncmp("exit", data->first_token->argv[0], 4) == 0)
		return (7);
	return (0);
}

//provisional, esta mal porque si me pasan echoasdaf, por ejemplo, lo cogeria como builtin, cuando en realidad no existe.