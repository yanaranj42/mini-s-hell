/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_error_messages.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:00:25 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 06:15:44 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	too_many_parameters(void)
{
	write(2, RED, ft_strlen(RED));
	write(2, "To run the program, no parameters other than", 44);
	write(2, " the executable itself are needed\n", 34);
	write(2, "Try again ✌️\n", 17);
	write(2, END, ft_strlen(END));
}
