/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/28 18:37:26 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//strjoinchar, que una un carácter a un string, y una variable tipo char *pretoken que vaya acumulando los chars para formar el string.

char *strjoinchar (char *str, char c) // METER EN EL LIBFT
{
	int i;
	char *new_str;

	printf ("     contenido de pretoken: |%s|\n", str);
	printf ("     char a añadir: |%c|\n\n", c);
	if (str == NULL && c == '\0')
		return (NULL);
	if (str)
		new_str = malloc(sizeof(char) * (ft_strlen(str) + 1 + 1));
	else
		new_str = malloc(sizeof(char) * (1 + 1));
	if (!new_str)
	{
		free (str);
		return (NULL);
	}
	i = 0;
	while (str && str[i] != '\0') // si no existe str ya me aseguro de que no entre en el while, pongo la condicion la primera a checkear, y al ser un and tienen que cumplirse ambas. si falla la primera no se mira la segunda y no hay peligro de que intente acceder a algo que no existe y pete
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	free (str);
	return (new_str);
} 
