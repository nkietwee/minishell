/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:10:26 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/11 00:16:43 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_execvecmd(char **cmd, char **path, t_minishell *ms)
{
	int		i;
	char	*path_exec;

	i = 0;
	if (*cmd[0] == '\0')
	{
		ft_putstr_fd("bash: : command not found\n", 2);
		return ;
	}
	while (path[i])
	{
		path_exec = ft_strjoinextra(path[i], cmd[0], NONE);
		if (access(path_exec, F_OK) == EXIT_SUCCESS)
		{
			cmd[0] = path_exec;
			if (execve(path_exec, cmd, ms->env) == -1)
				ft_putstr_fd("Can't execve\n", STDOUT_FILENO);
		}
		free(path_exec);
		i++;
	}
	if (path[i] == NULL)
		ft_prterrexec(cmd[0], ERR_CMD);
}

void	ft_execvepath(char **path, t_minishell *ms)
{
	if (access(path[0], F_OK | X_OK) == -1)
		ft_prterrexec(path[0], ERR_PATH);
	else
		execve(path[0], path, ms->env);
}

void	ft_close_pipe(t_minishell *ms, t_list *tb_lst)
{
	t_table	*table;

	table = (t_table *)(tb_lst->data);
	if (ms->nbr_cmd_all > 1)
	{
		close(table->fd_pipe[0]);
		close(table->fd_pipe[1]);
	}
}
