/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtpcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:31:45 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/10 15:00:51 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_findpath(char **env)
{
	int		i;
	char	**path;

	i = -1;
	i = 0;
	while (1)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' \
		&& env[i][2] == 'T' && env[i][3] == 'H')
			break ;
		i++;
	}
	path = ft_split(env[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoinextra(path[i], "/", BEFORE);
		i++;
	}
	return (path);
}
