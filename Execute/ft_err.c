/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:37:43 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/11 00:16:02 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_prterr_builtins(int mode, char *cmd, char *str)
{
	if (mode == PER_DN)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (mode == CANNT_OPEN)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

void	ft_prterrexec(char *str, int mode)
{
	if (mode == ERR_PATH || mode == NO_FILE)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (mode == PER_FILE)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (mode == ERR_CMD)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

void	ft_prterr(int mode, char *txt)
{
	if (mode == CANNT_PIPE)
		ft_putstr_fd("It can't create pipe", 2);
	else if (mode == CANNT_FORK)
		ft_putstr_fd("It can't fork", 2);
	else if (mode == CANNT_OPENIN)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(txt, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (mode == CANNT_OPENOUT)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(txt, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	exit (1);
}
