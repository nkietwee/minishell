/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:32:52 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/01 15:28:34 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(char **cmd , int fd_out)
{
	int	i;
	int	no_nl;

	i = 1; // i = 0 ->echo
	no_nl = 0;
	dprintf(2, "ft_echo\n");
	dprintf(2, "ft_out : %d\n", fd_out);
	if (ft_findstr(cmd[1], "-n", 2) == EXIT_SUCCESS)
	{
		no_nl = 1;
		i = 2;
	}
	while (cmd[i])
	{
		// ft_putstr_fd(cmd[i], STDOUT_FILENO);
		ft_putstr_fd(cmd[i], fd_out);
		i++;
		if (!cmd[i])
			break;
		ft_putstr_fd(" ", fd_out);
		// ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (no_nl == 0)
		write(fd_out, "\n", 1);
		// write(STDOUT_FILENO, "\n", 1);
	// exit(0);
}