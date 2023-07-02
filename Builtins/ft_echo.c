/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:56:16 by nkietwee          #+#    #+#             */
/*   Updated: 2023/07/01 18:26:27 by nkietwee         ###   ########.fr       */
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

/* // draft
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
} */

int  ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

/* echo have a new line 
echo - n don't have new line */
void    ft_echo(char **str, char option)
{
	int i;

	i = 0;
	printf("Echo\n");
	// if ((ft_findstr(str, "pwd", 3) == EXIT_SUCCESS) || (ft_findstr(str, "PWD", 3) == EXIT_SUCCESS))
	//     ft_pwd();
	// getenv 
	// if ac[0] = $
		//get
	while (str[i])
	{
		printf("%s", str[i]);
		i++;
		if (str != NULL)
			printf(" "); //  use space because arg is more than 1
	}
	if (option != 'n') //option is -n
		printf("\n");
}