/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:33:09 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/01 17:09:35 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(void)
{
	char *path;

	// dprintf(2, "pwd\n");
	path = getcwd(NULL, 0);
	if (!path)
		return ;
	printf("%s\n", path);
	free (path); //  path malloc
	// exit(0);
}