/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:29:38 by yanaranj          #+#    #+#             */
/*   Updated: 2024/08/21 13:03:09 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strnum(char *s)
{
	int	flag;

	flag = 0;
	if (s == NULL)
		return (0);
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			flag = 1;
		else
		{
			flag = 0;
			break ;
		}
		s++;
	}
	return (flag);
}

void    cases(t_general *data)
{
    char    **argv;

    argv = data->first_token->argv;
    if (check_long(argv[1]))
    {
        data->flag = -1;
        data->ret_exit = 255;
        break ;
    }
    if (num_args(data))
        data->flag = 1;
    else
        data->flag = -1;
}


static int  valid_arg(char *argv)
{
    /*int i;

    i = 0;
    if (argv[i] == '+' || argv[i] == '-')
        i++;*/
    if (ft_strnum(argv))
        return (1);
    return (0);
}

static int  check_long(char *str)
{
    //int len;
    int i;
    
    i = 0;
    //len = ft_strlen(str);
    if (valid_arg(str[i]) == 1)
    { 
        i++;
	    if (ft_strncmp((char *)LONG_MIN, argv[i], 19) == 0)
            printf(YELLOW"LONG_MIN\n"END);
        else if(ft_strncmp((char *)LONG_MAX, argv[i], 19)  == 0)
            printf(BLUE"LONG MAX\n"END);	
        return (1);		
    }
	return (0);
}

static int  num_args(t_general *data)
{
    char    *argv;

    argv = data->first_token->argv;
    if (argv[0] || argv[1])
	{
		if (argv[1] && !argv[2])
			return (data->ret_exit = ft_atoi(argv[1]));
	}
    if (argv[2])
    {
        if (valid_arg(argv[1]))
            ft_putstr_fd()
    }
}
