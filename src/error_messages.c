/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:05:12 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/24 22:14:05 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "minishell.h"

void	no_such_file_or_directory(char *start)
{
	write(2, RED, ft_strlen(RED)); // BORRAR
	write(2, "💀 bash: ", 11);
	write(2, start, ft_strlen(start));
	write(2, ": No such file or directory", 27);
	write(2, END, ft_strlen(END)); // BORRAR
	write(2, "\n", 1);
	exit(127);
}

void	permission_denied(char *start)
{
	write(2, RED, ft_strlen(RED)); // BORRAR
	write(2, "💀 bash: ", 11);
	write(2, "Permission denied: ", 19);
	write(2, start, ft_strlen(start));
	write(2, END, ft_strlen(END)); // BORRAR
	write(2, "\n", 1);
	exit(126);
}

void	command_not_found(char *start)
{
	write(2, RED, ft_strlen(RED)); // BORRAR
	write(2, "💀 bash: ", 11);
	write(2, "Command not found: ", 19);
	write(2, start, ft_strlen(start));
	write(2, END, ft_strlen(END)); // BORRAR
	write(2, "\n", 1);
	exit(127);
}

void	unexpected_token_message(char *message)
{
	write(2, RED, ft_strlen(RED));
	write(2, "💀 bash: ", 11);
	write(2, "syntax error near unexpected token ", 35);
	write(2, message, ft_strlen(message));
	write(2, END, ft_strlen(END));
	write(2, "\n", 1);

	//BORRAR:
	write(2, "\n", 1);
	write(2, GREEN, ft_strlen(GREEN));
	write(2, "******************* FREE *******************\n", 45);
	write(2, END, ft_strlen(END));
}

void	perror_message(char *start, char *message)
{
	if (start)
	{
		write(2, RED, ft_strlen(RED));
		write(2, "💀 bash: ", 11);
		write(2, start, ft_strlen(start));
		write(2, ": ", 2);
		write(2, END, ft_strlen(END));
	}
	perror(message);
}

void ambiguous_redirect (char *start)
{

	write(2, RED, ft_strlen(RED));
	write(2, "💀 bash: ", 11);
	write(2, start, ft_strlen(start));
	write(2, ": ambiguous redirect", 20);
	write(2, END, ft_strlen(END));
}

int	error_opt(char *s1, char *s2, char **arr, char *argv)
{
	ft_putstr_fd("minishell: export: `", STDOUT);
	ft_putstr_fd(s1, STDOUT);
	if (ft_strchr(argv, '='))
		ft_putstr_fd("=", STDOUT);
	if (s2 == NULL)
		s2 = ft_strdup("");
	ft_putstr_fd(s2, STDOUT);
	ft_putstr_fd(": not a valid identifier\n", STDOUT);
	arr_clean(arr);
	return (0);
}

void	error_brk(t_general *data, char *msg, char *name, int flag)
{
	if (name || msg)
		ft_putstr_fd("minishell: ", STDERR);
	if ((flag == 1 && *name && !msg) || flag == 12 || flag == 14)
		perror(name);
	else if (name)
	{
		ft_putstr_fd(name, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (msg)
	{
		ft_putstr_fd(msg, STDERR);	
		ft_putstr_fd("\n", STDERR);	
	}
	data->exit_status = flag;
	free_exit(data);
}