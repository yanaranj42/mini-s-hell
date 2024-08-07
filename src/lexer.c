/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:03:18 by yanaranj          #+#    #+#             */
/*   Updated: 2024/08/07 16:13:33 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
/* por ahora solo estoy poniendo el check de los espacios
* se controla tambien los \t y \n??
*/
#include <unistd.h>
/*char check_pipe(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
		{
			while (s[i] == ' ')
			{
				if (s[i + 1] == '|')
					write
			}	
		}
	}
}*/

char del_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
		{
			if (s[i + 1] > ' ' && s[i + 1] != '\0')
				write(1, " ", 1);
		}
		else if (s[i] != ' ')
			write(1, &s[i], 1);
		i++;
	}
	return (1);
}

int main(int ac, char **av)
{
	if (ac > 1)
	{
		del_space(av[1]);
	}
	return (0);
}