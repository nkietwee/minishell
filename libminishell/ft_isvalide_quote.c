/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalide_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:01:31 by ptungbun          #+#    #+#             */
/*   Updated: 2023/09/17 01:43:36 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isvalide_quote(char *str, char quote)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (str[i] == quote)
			return (1);
		i++;
	}
	return(0);
}
