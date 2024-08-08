/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 03:01:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/08 03:12:50 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//funcion para recibir un string (argv[0] del token) y determino si se corresponde a un builtin o no devolviendo true o false (strcmp)
//si es un builin, llamare a executor builtin, sino, en un futuro llamare executor command (que tendra execve)


