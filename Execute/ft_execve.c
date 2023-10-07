/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:10:26 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/07 23:50:31 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		dprintf(2, "path_exec : %s\n", path_exec);
		if (access(path_exec, F_OK) == EXIT_SUCCESS)
		{
			// cmd[0] = path_exec;
			dprintf(2, "cmd[0] : %s\n", cmd[0]);
			if (execve(path_exec, cmd, env) == -1)
			{
				ft_putstr_fd("Can't execve\n" , STDOUT_FILENO);
				// exit(0);
			}
		}
		free(path_exec);
		i++;
	}
	// dprintf(2, "path_exec____ \n");
	if (path[i] == NULL)
		ft_prterrexec(cmd[0], 1, ERR_CMD);
}

void	ft_execvepath(char **path, char **tmp_env)
{
	dprintf(2, "Entry : execvepath\n");
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

void	ft_parent_do_nothing(t_minishell *ms, t_list *tb_lst)
{
	t_table	*table;
	// t_data exec_data;
	// dprintf(2, "Hello from parent\n");
	table = (t_table *)(tb_lst->data);
	// exec_data = (t_data)(table->exec_data);
	table->fd_tmp = dup(table->fd_pipe[0]); // another process can read from previos process
	ft_close_pipe(ms, tb_lst);
}


void	ft_parent_builtin(t_minishell *ms, t_list *tb_lst)
{
	t_table	*table;
	// t_dict	*tmp_env;

	table = (t_table *)(tb_lst->data);
	// ft_getfd(ms, tb_lst);
	table->fd_tmp = dup(table->fd_pipe[0]);
	ft_close_pipe(ms, tb_lst);
	if (table->exec_status == 2)
	{
		dprintf(2, "ft_parent_builtin\n");
		if (ft_strcmp(table->cmd[0], "cd") == 0)
			ft_cd(table->cmd, ms->dict);
		if ((ft_strcmp(table->cmd[0], "export") == 0) && table->cmd[1])
			ft_export(table->cmd,  &ms->dict);
		if (ft_strcmp(table->cmd[0], "unset") == 0)
			ft_unset(table->cmd, &ms->dict);
		if (ft_strcmp(table->cmd[0], "exit") == 0)
			ft_exit(table->cmd, ms->dict);
	}
}

void	ft_child_exve(t_minishell *ms, t_list *tb_lst)
{
	t_table	*table;
	// t_data	*exec_data;
	char	**path;

	table = (t_table *)(tb_lst->data);
	// exec_data = (t_data *)(&(table->exec_data));
	path = ft_findpath(ms->env); // fixed from env to t_dict *dict
	// ft_getfd(ms, tb_lst);
	// if (table->fd_in == -1)
	// 	return ;
	ft_dup2(ms, tb_lst);
	ft_close_pipe(ms, tb_lst);
	if (ft_findchar(table->cmd[0], '/') == EXIT_SUCCESS) // cmd or av4
		ft_execvepath(table->cmd, ms->env);
	else
	{
		// dprintf(2, "ft_child_exve %d\n", table->i);
		ft_execvecmd(table->cmd, path, ms->env);
	}
}

void	ft_child_builtin(t_minishell *ms, t_list *tb_lst)
{
	t_table	*table;
	// t_data	*exec_data;

	table = (t_table *)(tb_lst->data);
	// exec_data = (t_data *)(&(table->exec_data));
	// ft_getfd(ms, tb_lst);
	// if (table->fd_in == -1)
	// 	return ;
	ft_dup2(ms, tb_lst);
	ft_close_pipe(ms, tb_lst);
	if (table->exec_status == 1)
	{
		if ((ft_strcmp(table->cmd[0], "export") == 0) && !table->cmd[1])
			ft_export(table->cmd,  &ms->dict);
		if (ft_strcmp(table->cmd[0], "echo") == 0)
			ft_echo(table->cmd , table->fd_out);
		if (ft_strcmp(table->cmd[0], "pwd") == 0)
			ft_pwd();
		if (ft_strcmp(table->cmd[0], "env") == 0)
			ft_env(ms->dict);
	}
}

void	ft_child_do_nothing(t_minishell *ms, t_list *tb_lst)
{
	// t_table	*table;
	// t_data	*exec_data;

	// table = (t_table *)(tb_lst->data);
	ft_close_pipe(ms, tb_lst);
	// exit(0);
}

void ft_close_pipe(t_minishell *ms, t_list *tb_lst)
{
	t_table	*table;

	table = (t_table *)(tb_lst->data);
	if (ms->nbr_cmd > 1)
	{
		close(table->fd_pipe[0]);
		close(table->fd_pipe[1]);
	}
}
/* void	ft_child(t_list *tb_lst, int nbr_cmd, t_dict *dict, int *table->fd_tmp)
{
	char **cmd;
	t_table	*table;
	t_data	*exec_data;
	char	**path;

	// check unset path
	table = (t_table *)(tb_lst->data);
	exec_data = (t_data *)(&(table->exec_data));
	// int i = -1;
	// while (table->tmp_env[++i])
	// 	dprintf(2, "env[%d] : %s\n", i, table->tmp_env[i]);
	// printf("findpath1\n");
	// exit(0);
	path = ft_findpath(table->tmp_env); // fixed from env to t_dict *dict
	// exit(0);
	// dprintf(2, "Hello from child\n");
	// ft_prtcmd(tb_lst, table->i);
	// dprintf(2, "fd_here_child_1 : %d\n", table->fd_heredoc);
	ft_getfd(tb_lst);
	// dprintf(2, "fd_here_child_2 : %d\n", table->fd_heredoc);
	if (exec_data->fd_in == -1)
		return ;
	ft_dup2(table->i, tb_lst, table->fd_tmp, nbr_cmd);
	// dprintf(2, "fd_inchild_2 : %d\n", exec_data->fd_in);
	// dprintf(2, "fd_outchild_2 : %d\n", exec_data->fd_out);
	// ft_builtin_child(table->cmd, env, exec_data->fd_out);
	// if (table->fd_heredoc > 2)
	// 	close(table->fd_heredoc);
	if (nbr_cmd > 1)
	{
		close(exec_data->fd_pipe[0]);
		close(exec_data->fd_pipe[1]);
	}
	if (ft_findchar(table->cmd[0], '/') == EXIT_SUCCESS) // cmd or av4
		ft_execvepath(table->cmd, table->tmp_env);
	else
		ft_execvecmd(table->cmd, path, table->tmp_env);
} */
