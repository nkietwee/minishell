/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:16:56 by ptungbun          #+#    #+#             */
/*   Updated: 2023/10/04 12:36:42 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strrchr(char *s, int c)
{
	int		i;
	char	*save;

	i = 0;
	save = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] == (unsigned char)c)
		{
			save = (char *)(s + i);
		}
		i++;
	}
	return (save);
}
