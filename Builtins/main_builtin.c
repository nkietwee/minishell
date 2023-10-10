/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 02:58:16 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/10 00:00:40 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_findstr(char *str, char *find, int len)
{
	int	i;

	i = 0;
	while (find[i] == str[i])
	{
		i++;
		if (i == len && str[i] == '\0')
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
