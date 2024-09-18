/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 01:22:21 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/18 18:55:03 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Escribe la cadena s en el descriptor de archivo fd.

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}
/*
int main(void)
{
	int fd;
	char *s = "hola";
	
	fd = open("test.txt", O_RDWR | O_CREAT);
	if (fd < 0)
		return (0);
	ft_putstr_fd (s, fd);
	close(fd);
	printf("fd: |%d| ", fd);
	return (0);
}*/
