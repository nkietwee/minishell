/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 01:52:32 by ptungbun          #+#    #+#             */
/*   Updated: 2023/10/04 12:36:42 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	i;

	if (dest == src || n == 0)
		return (dest);
	if (dest > src && dest - src < (int)n)
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i--;
		}
		return (dest);
	}
	if (src > dest && src - dest < (int)n)
	{
		i = 0;
		while (i < (int)n)
		{
			*(char *)(dest + i) = *(char *)(src + i);
			i++;
		}
		return (dest);
	}
	return (ft_memcpy(dest, src, n));
}
