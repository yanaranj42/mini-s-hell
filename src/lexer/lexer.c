/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:39:24 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/08 14:17:19 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void delete_spaces (char *line)
{
	line = ft_strtrim(line, " ");
	printf("line post strtrim:%s\n", line);
}


int lexer (char *line)
{
	delete_spaces(line);
	printf ("linea de comandos despues de strtrim: %s\n", line);


	return (1);
}