/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:56:16 by nkietwee          #+#    #+#             */
/*   Updated: 2023/06/26 00:09:55 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

//len : len of find
int ft_findstr(char *str, char *find, int len)
{
	int	i;

	i = 0;
    // printf("len :%d\n" , len);

    while (find[i] == str[i])
    {
        i++;
        if (i == len && str[i] == '\0')
            return(EXIT_SUCCESS);
    }
    return (EXIT_FAILURE);
}

int  ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (-1);
		i++;
	}
    return (0);
}

void    ft_echo(char *str)
{
    printf("Echo\n");
    if ((ft_findstr(str, "pwd", 3) == EXIT_SUCCESS) || (ft_findstr(str, "PWD", 3) == EXIT_SUCCESS))
        ft_pwd();
    // getenv 
}