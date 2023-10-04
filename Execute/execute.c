/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:26:45 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/04 19:58:45 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_check_builtin(char **cmd)
{
	//check if command is not builtin function return 0
	// but if it's builtin function return 1 or 2
	// 1 mean execute in child process
	// 2 mean execute in parent process
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	if (!ft_strcmp(cmd[0], "export") && !cmd[1])
		return (1);
	if (!ft_strcmp(cmd[0], "export") && cmd[1])
		return (2);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (2);
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (2);
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (2);
	return (0);
}

/*close fd after dup */
void ft_dup2(int i, t_list *tb_lst, int *table->fd_tmp, int nbr_cmd)
{
	t_table *table;
	t_data *exec_data;

	table = (t_table *)(tb_lst->data);
	exec_data = (t_data *)(&(table->exec_data));
	// dprintf(2, "i : %d\n", i);
	// dprintf(2, "nbr_cmd : %d\n", nbr_cmd);

	if (i == 0 && nbr_cmd == 1) // for 1 cmd
	{
		// dprintf(2, "fd_in_dup2 : %d\n" , exec_data->fd_in);
		// dprintf(2, "fd_here_dup2 : %d\n" , table->fd_heredoc );
		// dprintf(2, "fd_out_dup2 : %d\n", exec_data->fd_out);
		dup2(exec_data->fd_in, STDIN_FILENO);
		dup2(exec_data->fd_out, STDOUT_FILENO);
		// dprintf(exec_data->fd_out, "finish_dup\n");
		if (exec_data->fd_in != STDIN_FILENO )
			close(exec_data->fd_in);
		if (exec_data->fd_out != STDOUT_FILENO)
			close(exec_data->fd_out);

	}
	else if (i == 0 && nbr_cmd > 1) // start with  > 1 cmd
	{
		// dprintf(2, "dup 1 cmd\n");
		dup2(exec_data->fd_in, STDIN_FILENO);
		dup2(exec_data->fd_pipe[1], STDOUT_FILENO);
	}
	else if (i == nbr_cmd - 1) // end
	{
		// dprintf(2 , "last cmd\n");
		// printf("fd_out : %d\n", exec_data->fd_out);
		exec_data->fd_out = STDOUT_FILENO; // for test
		dup2(*table->fd_tmp, STDIN_FILENO);
		dup2(exec_data->fd_out, STDOUT_FILENO);
	}
	else //btw
	{
		// printf("btw cmd\n");
		dup2(*table->fd_tmp, STDIN_FILENO);
		dup2(exec_data->fd_pipe[1], STDOUT_FILENO);
	}
}

// void ft_initdata_exec(t_list *tb_lst)
void ft_initdata_exec(t_list *tb_lst, char **env)
{
	t_table *table;
	int	i_cnt = 0;
	table = (t_table *)(tb_lst->data);
	table->tmp_env = env;
	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		table->i = i_cnt;
		table->exec_data.pid = 0;
		table->exec_data.fd_in = 0;
		table->exec_data.fd_out = 0;
		table->exec_data.fd_pipe[0] = 0;
		table->exec_data.fd_pipe[1] = 0;
		table->exec_data.nbr_infile = ft_cnt_infile(tb_lst);
		table->exec_data.nbr_out_append = 0;
		table->exec_data.nbr_heredoc = ft_cnt_heredoc(tb_lst);
		table->fd_tmp = 0;
		dprintf(2, "[%d] heredoc : %d\n" , i_cnt, table->exec_data.nbr_heredoc);
		// table->exec_data.fd_heredoc = 0;
		// table->
		i_cnt++;
		tb_lst = tb_lst->next;
	}
}

void ft_waitpid(t_list *tb_lst_cpy)
{
	t_table	*table_cpy;
	t_data	data_exec_cpy;

	while (tb_lst_cpy)
	{
		table_cpy = (t_table *)(tb_lst_cpy->data);
		data_exec_cpy = (table_cpy->exec_data) ;
		waitpid(data_exec_cpy.pid, NULL, 0);
		tb_lst_cpy = tb_lst_cpy->next;
	}
}
// void ft_execute(t_list *tb_lst, t_dict *dict, int nbr_cmd)
void ft_execute(t_minishell *ms, t_list *tb_lst, int nbr_cmd)
{
	t_table	*table;
	t_data	*data_exec;
	t_list	*tb_lst_cpy = NULL;
	table->i = 0;

	// (void)dict;
	tb_lst_cpy = tb_lst;
	while (tb_lst && table->i < nbr_cmd)
	{
		// dprintf(2, "tb_lst_1\n");
		table = (t_table *)(tb_lst->data);
		data_exec = (t_data *)(&(table->exec_data));
		if (table->i != nbr_cmd -1)
		{
			if (pipe(data_exec->fd_pipe) == -1)
				ft_prterr(CANNT_PIPE, "Pipe");
		}
		table->exec_status = ft_check_builtin(table->cmd);
		data_exec->pid = fork();
		if (data_exec->pid == -1)
			ft_prterr(CANNT_FORK, "Fork");
		if (data_exec->pid == 0 && ft_check_builtin(table->cmd) == EXIT_FAILURE)
			branch_child(ms, tb_lst, ms->env);
		if (data_exec->pid > 0)
			branch_parent(ms, tb_lst);
		table->i++;
		tb_lst = tb_lst->next;
	}
	// close(data_exec->fd_out);
	// close(data_exec->fd_in);
	ft_waitpid(tb_lst_cpy);
}

void branch_parent(t_minishell *ms, t_list *tb_lst)
{
	t_table	*table;

	table = (t_table *)(tb_lst->data);
	if (!table->exec_status)
		ft_parent(ms, tb_lst);
	else if (table->exec_status == 2)
		ft_parent_builtin(ms, tb_lst);
	else //table->exec_status == 1
		ft_do_nothing(ms, tb_lst);
}

void branch_child(t_list *tb_lst, char **env, int nbr_cmd)
{
	t_table	*table;

	table = (t_table *)(tb_lst->data);
	if (!table->exec_status)
		ft_child(ms, tb_lst);
	else if (table->exec_status == 1)
		ft_child_builtin(ms, tb_lst);
	else //table->exec_status == 2
		ft_do_nothing(ms, tb_lst);
}
