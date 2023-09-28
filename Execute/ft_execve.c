/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:10:26 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/29 01:09:03 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_execvecmd(char **cmd, char **path, char **tmp_env)
{
	int		i;
	char	*path_exec;

	i = 0;
	if (!cmd)
		return ;
	// printf("ft_execvecmd\n");
	while (path[i])
	{
		path_exec = ft_strjoinextra(path[i], cmd[0], NONE);
		if (access(path_exec, F_OK) == EXIT_SUCCESS)
		{
			execve(path_exec, cmd, tmp_env);
		}
		free(path_exec);
		i++;
	}
	if (path[i] == NULL)
		ft_prterrexec(cmd[0], 1, ERR_CMD);
}

void	ft_execvepath(char **path, char **tmp_env)
{
	// printf("Entry : execvepath\n");
	if (access(path[0], F_OK | X_OK) == -1)
	{
		ft_prterrexec(path[0], 1, ERR_PATH);
		printf("not access\n");
		// ft_dbfree((void **)path); // ??
	}
	else
	{
		// printf("path\n");
		execve(path[0], path, tmp_env);
	}
}

void	ft_parent(t_list *tb_lst, int i , int *fd_tmp_read)
{
	// printf ("ft_parent\n");
	// exit (0);
	t_table	*table;
	t_data data_exec;

	// tb_lst = tb_lst->next;
	// if (i == 1)
	// 	exit(0);
	table = (t_table *)(tb_lst->data);
	data_exec = (t_data )(table->exec_data);
	*fd_tmp_read = dup(data_exec.fd_pipe[0]); // another process can read from previos process
	// printf("tmp_read : %d\n" , data->fd_tmp_read);
	close(data_exec.fd_pipe[0]);
	close(data_exec.fd_pipe[1]);

	// export
	// cd
	// unset
	// exit
}

void	ft_prtcmd(t_list *tb_lst)
{
	t_table *table;

	table = (t_table *)(tb_lst->data);
	printf("cmd : %s\n", table->cmd[0]);


}
void	ft_child(t_list *tb_lst, int i, char **env, int *fd_tmp_read)
{
	char **cmd;
	t_table	*table;
	t_data	data_exec;
	char	**path;

	path = ft_findpath(env);
	// dprintf(2, "ft_child\n");
	// ft_countexec(tb_list);
	ft_prtcmd(tb_lst);
	table = (t_table *)(tb_lst->data);
	data_exec = (t_data)(table->exec_data);
	// if (ft_check_buildin(table->cmd) == EXIT_SUCCESS)
	// 	ft_parent(tb_lst);
	ft_dup2(i, &data_exec, *fd_tmp_read);
	close(data_exec.fd_pipe[0]);
	close(data_exec.fd_pipe[1]);
	if (ft_findchar(table->cmd[0], '/') == EXIT_SUCCESS) // cmd or av4
		ft_execvepath(table->cmd, env);
	else
		ft_execvecmd(table->cmd, path, env);
}
