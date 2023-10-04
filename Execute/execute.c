/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:26:45 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/05 02:16:43 by pnamwayk         ###   ########.fr       */
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
void ft_dup2(t_minishell *ms, t_list *tb_lst)
{
	t_table *table;
	// t_data *exec_data;

	table = (t_table *)(tb_lst->data);
	// exec_data = (t_data *)(&(table->exec_data));
	// dprintf(2, "fd_in = %d  fd_out = %d\n",table->fd_in, table->fd_out);
	//infile
	if (table->nbr_infile)
		dup2(table->fd_in, STDIN_FILENO);
	else if (table->i != 0)
		dup2(table->fd_tmp, STDIN_FILENO);
	//outfile
	if (table->nbr_outfile)
		dup2(table->fd_out, STDOUT_FILENO);
	else if (table->i != ms->nbr_cmd - 1 && ms->nbr_cmd > 1)
		dup2(table->fd_pipe[1], STDOUT_FILENO);
	// dprintf(2, "fd_in = %d  fd_out = %d\n",table->fd_in, table->fd_out);


}

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
		// dprintf(2, "cmd[%d] : %s----------------------\n" , table->i, table->cmd[0]);
		// table->pid = 0;
		// table->fd_in = 0;
		// table->fd_out = 0;
		// table->fd_pipe[0] = 0;
		// table->fd_pipe[1] = 0;
		table->nbr_infile = ft_cnt_infile(tb_lst);
		table->nbr_outfile = ft_cnt_outfile(tb_lst);
		table->nbr_heredoc = ft_cnt_heredoc(tb_lst);
		// dprintf(2, "[%d] nbr_infile : %d\n" , table->i, table->nbr_infile);
		// table->exec_data.nbr_out_append = 0;
		// dprintf(2, "[%d] nbr_outfile : %d\n" , table->i, table->nbr_outfile);
		// dprintf(2, "[%d] heredoc : %d\n" , table->i, table->nbr_heredoc);
		i_cnt++;
		tb_lst = tb_lst->next;
	}
}

void ft_waitpid(t_minishell *ms, t_list *tb_lst_cpy)
{
	(void) ms;
	t_table	*table_cpy;
	t_data	data_exec_cpy;

	while (tb_lst_cpy)
	{
		table_cpy = (t_table *)(tb_lst_cpy->data);
		data_exec_cpy = (table_cpy->exec_data) ;
		waitpid(ms->pid[table_cpy->i], NULL, 0);
		tb_lst_cpy = tb_lst_cpy->next;
	}
	// t_table	*table;
	// while (i < ms->nbr_cmd)
	// {
	// 	table = (t_table *)(tb_lst->data);
	// 	waitpid(table->pid, NULL, 0);
	// 	tb_lst = tb_lst->next;
	// }
}
// void ft_execute(t_list *tb_lst, t_dict *dict, int nbr_cmd)
void ft_execute(t_minishell *ms, t_list *tb_lst)
{
	t_table	*table = NULL;
	t_data	*data_exec;
	t_list	*tb_lst_cpy = NULL;
	int i = 0;

	// (void)dict;
	tb_lst_cpy = tb_lst;
	ms->pid = malloc(sizeof(pid_t) * ms->nbr_cmd);
	while (i < ms->nbr_cmd)
	{
		table = (t_table *)(tb_lst->data);
		data_exec = (t_data *)(&(table->exec_data));
		// dprintf(2, "tb_lst_1\n");
		if (table->i != ms->nbr_cmd -1)
		{
			if (pipe(table->fd_pipe) == -1)
				ft_prterr(CANNT_PIPE, "Pipe");
		}
		table->exec_status = ft_check_builtin(table->cmd);
		ms->pid[i] = fork();
		if (ms->pid[i] == -1)
			ft_prterr(CANNT_FORK, "Fork");
		else if (ms->pid[i] == 0)
			branch_child(ms, tb_lst);
		else //if (table->pid > 0)
			branch_parent(ms, tb_lst);
		i++;
		tb_lst = tb_lst->next;
	}
	// close(data_exec->fd_out);
	// close(data_exec->fd_in);
	ft_waitpid(ms, tb_lst_cpy);
	free(ms->pid);
}

void branch_parent(t_minishell *ms, t_list *tb_lst)
{
	t_table	*table;

	table = (t_table *)(tb_lst->data);
	dprintf(2, "---parent[%d] table->exec_status: %d\n", table->i, table->exec_status);
	if (table->exec_status == 2)
		ft_parent_builtin(ms, tb_lst);
	else //table->exec_status == 1
		ft_parent_do_nothing(ms, tb_lst);
}

void branch_child(t_minishell *ms, t_list *tb_lst)
{
	t_table	*table;

	table = (t_table *)(tb_lst->data);
	dprintf(2, "---child[%d] table->exec_status: %d\n", table->i, table->exec_status);
	if (!table->exec_status)
		ft_child_exve(ms, tb_lst);
	else if (table->exec_status == 1)
		ft_child_builtin(ms, tb_lst);
	else //table->exec_status == 2
		ft_child_do_nothing(ms, tb_lst);
}

