/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 05:48:56 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/11 00:27:34 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_child_execve(t_minishell *ms, t_list *tb_lst, int *fd_read)
{
	t_table	*table;
	t_data	*exec_data;
	char	**path;

	table = (t_table *)(tb_lst->data);
	exec_data = (t_data *)(&(table->exec_data));
	if (ft_checkpath(ms->dict) == 0)
	{
		ft_prterrexec(table->cmd[0], ERR_PATH);
		return ;
	}
	path = ft_findpath(ms->env);
	ft_getfd(tb_lst);
	if (exec_data->fd_in == -1 || exec_data->fd_out == -1)
		return ;
	ft_dup2(tb_lst, fd_read, ms->nbr_cmd_all);
	ft_close_pipe(ms, tb_lst);
	if (table->cmd[0])
	{
		if (ft_findchar(table->cmd[0], '/') == EXIT_SUCCESS)
			ft_execvepath(table->cmd, ms);
		else
			ft_execvecmd(table->cmd, path, ms);
	}
}

void	ft_check_unset(t_minishell *ms)
{
	t_table	*table;

	table = (t_table *)(ms->tb_lst->data);
	if (table->exec_status != CMD_)
		return ;
	if (ft_checkpath(ms->dict) == 0)
	{
		ft_prterrexec(table->cmd[0], ERR_PATH);
		return ;
	}
}

void	ft_child_builtin(t_minishell *ms, t_list *tb_lst, int *fd_read)
{
	t_table	*table;
	t_data	*exec_data;

	table = (t_table *)(tb_lst->data);
	exec_data = (t_data *)(&(table->exec_data));
	ft_check_unset(ms);
	ft_getfd(tb_lst);
	if (exec_data->fd_in == -1 || exec_data->fd_out == -1)
		return ;
	ft_dup2(tb_lst, fd_read, ms->nbr_cmd_all);
	ft_close_pipe(ms, tb_lst);
	if (table->exec_status == BUI_CHILD)
	{
		if ((ft_strcmp(table->cmd[0], "export") == 0) && table->cmd[1] == NULL)
			ft_export(table->cmd, &ms->dict);
		if (ft_strcmp(table->cmd[0], "echo") == 0)
			ft_echo(table->cmd, exec_data->fd_out);
		if (ft_strcmp(table->cmd[0], "pwd") == 0)
			ft_pwd();
		if (ft_strcmp(table->cmd[0], "env") == 0)
			ft_env(ms->dict);
	}
}

void	ft_child_do_nothing(t_minishell *ms, t_list *tb_lst)
{
	ft_close_pipe(ms, tb_lst);
}

void	branch_child(t_minishell *ms, t_list *tb_lst, int *fd_read)
{
	t_table	*table;

	table = (t_table *)(tb_lst->data);
	if (table->exec_status == CMD_)
		ft_child_execve(ms, tb_lst, fd_read);
	else if (table->exec_status == BUI_CHILD)
		ft_child_builtin(ms, tb_lst, fd_read);
	else
		ft_child_do_nothing(ms, tb_lst);
	exit(ms->exit_code);
}
