/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:33:09 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/05 02:31:22 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if (!path)
		return ;
	// write(fd_op)
	// printf("%s\n", path);
	ft_putstr_fd(path, STDOUT_FILENO);
	// printf("%s\n", path);
	free (path); //  path malloc
	// exit(0);
}
