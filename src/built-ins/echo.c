/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:41:00 by yanaranj          #+#    #+#             */
/*   Updated: 2024/08/13 13:51:50 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  args_counter(char **argv)
{
    int i;
    
    i = 0;
    while (argv[i])
        i++;
    return (i);
}
int ft_echo(char **argv)
{
    int i;
    int n_opt;

    i = 1;
    n_opt = 0;
    if (args_counter(argv) > 1)
    {
        while (argv[i] && (ft_strncmp(argv[i], "-n", 1) == 0))
        {
            n_opt = 1;
            i++;
        }
        while (argv[i])
        {
            ft_putstr_fd(argv[i], 1);
            if (argv[i + 1] && argv[i][0] != '\0')
                write(1, " ", 1);
            i++;
        }
        if (n_opt == 0)
            write(1, "\n", 1);
    }
    return (SUCCESS);
}
