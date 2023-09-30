/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:10:26 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/01 02:49:47 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_execvecmd(char **cmd, char **path, char **env)
{
	int		i;
	char	*path_exec;

	i = 0;
	if (!cmd)
		return ;
	while (path[i])
	{
		path_exec = ft_strjoinextra(path[i], cmd[0], NONE);
		// free(cmd[0]);
		// dprintf(2, "path_exec : %s\n", path_exec);
		if (access(path_exec, F_OK) == EXIT_SUCCESS)
		{
			cmd[0] = path_exec;
			// dprintf(2, "cmd : %s\n", cmd[0]);
			// dprintf(2, "cmd : %s\n", cmd[1]);
			// dprintf(2, "path_exec : %s\n", path_exec);
			if (execve(path_exec, cmd, env) == -1)
			{
				dprintf(2, "Can't execve\n");
				exit(0);
			}
		}
		free(path_exec);
		i++;
	}
	if (path[i] == NULL)
		ft_prterrexec(cmd[0], 1, ERR_CMD);
}

void	ft_execvepath(char **path, char **tmp_env)
{
	// dprintf(2, "Entry : execvepath\n");
	if (access(path[0], F_OK | X_OK) == -1)
	{
		ft_prterrexec(path[0], 1, ERR_PATH);
		// ft_dbfree((void **)path); // ??
	}
	else
		execve(path[0], path, tmp_env);
}

void	ft_prtcmd(t_list *tb_lst, int i)
{
	t_table *table;

	table = (t_table *)(tb_lst->data);
	printf("cmd[%d] : %s\n", i, table->cmd[0]);

}

void	ft_parent(t_list *tb_lst, int i , int *fd_tmp_read, int nbr_cmd)
{
	t_table	*table;
	t_data exec_data;

	dprintf(2, "Hello from parent\n");
	ft_prtcmd(tb_lst, i);
	table = (t_table *)(tb_lst->data);
	exec_data = (t_data )(table->exec_data);
	*fd_tmp_read = dup(exec_data.fd_pipe[0]); // another process can read from previos process
	// printf("tmp_read : %d\n" , data->fd_tmp_read);
	if (nbr_cmd > 1)
	{
		close(exec_data.fd_pipe[0]);
		close(exec_data.fd_pipe[1]);
	}
	// if (data_exec.pid != 0) // espectialy parent
	// dprintf(2, "c1\n");
	// ft_waitpid(tb_lst);


	// export
	// cd
	// unset
	// exit
}

void	ft_child(t_list *tb_lst, int nbr_cmd, char **env, int *fd_tmp_read)
{
	char **cmd;
	t_table	*table;
	t_data	*exec_data;
	char	**path;

	path = ft_findpath(env);
	table = (t_table *)(tb_lst->data);
	exec_data = (t_data *)(&(table->exec_data));
	dprintf(2, "Hello from child\n");
	ft_prtcmd(tb_lst, table->i);
	ft_getfd(tb_lst);
	// printf("fd_in_child :  %d\n", exec_data->fd_in);
	ft_dup2(table->i, tb_lst, fd_tmp_read, nbr_cmd);
	if (exec_data->fd_heredoc > 2)
		close(exec_data->fd_heredoc);
	if (nbr_cmd > 1)
	{
		close(exec_data->fd_pipe[0]);
		close(exec_data->fd_pipe[1]);
	}
	if (ft_findchar(table->cmd[0], '/') == EXIT_SUCCESS) // cmd or av4
		ft_execvepath(table->cmd, env);
	else
		ft_execvecmd(table->cmd, path, env);
}
