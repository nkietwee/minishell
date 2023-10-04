/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 01:33:17 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/04 12:36:42 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

// int	main(int ac, char **av)
// {
// 	int	i;

// 	i = 1;
// 	printf("Success %d\n", EXIT_SUCCESS);
// 	printf("Failure %d\n", EXIT_FAILURE);
// 	while (av[i])
// 	{
// 		printf("%c : %d\n", av[i][0], ft_isalpha(av[i][0]));
// 		i++;
// 	}
// }
