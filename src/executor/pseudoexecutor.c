/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudoexecutor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 01:50:35 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/08 03:12:11 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//este pseudoexecutor va a recibir el data, mirara el argv[0] del token, va a comprobar si ese argv[0] se corresponde a un builtin y entonces va a llamar a la funcion execute builtin que va a llamar al builtin que le toca. 
//si llamo a env que llame al builtin env
//si llamo a exit que llame al builtin exit en vez de hacer el parche que tenemos de momento
//el executor llamara a los builins como si fueran comandos, pero en vez de hacer un execve, los llama directamente

//luego ampliaremos, ahora es para empezar a jugar con los builtins
//el pseudo executor en el futuro iterara sobre los tokens, y abrira pipes y redirecciones si toca, luego mirara el comando a ejecutar y lo ejecutara (executor builtin, executor cmd), y luego cerrara redirecciones y pipes si tiene que hacerlo
