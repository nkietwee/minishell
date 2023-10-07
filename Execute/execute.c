/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:26:45 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/08 02:53:51 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*close fd after dup */
void ft_dup2(t_list *tb_lst, int *fd_tmp_read, int nbr_cmd)
{
	t_table *table;
	t_data *exec_data;

	table = (t_table *)(tb_lst->data);
	exec_data = (t_data *)(&(table->exec_data));
	// dprintf(2, "i_dup2 : %d\n", exec_data->i);
	// dprintf(2, "nbr_cmd_dup2 : %d\n", nbr_cmd);

	if (exec_data->i == 0 && nbr_cmd == 1) // for 1 cmd
	{
		// dprintf(2, "dup for 1 cmd\n");
		// dprintf(2, "fd_in_dup2_bf : %d\n" , exec_data->fd_in);
		// dprintf(2, "fd_here_dup2 : %d\n" , table->fd_heredoc );
		// dprintf(2, "fd_out_dup2_bf : %d\n", exec_data->fd_out);
		dup2(exec_data->fd_in, STDIN_FILENO);
		dup2(exec_data->fd_out, STDOUT_FILENO);
		if (exec_data->fd_in != STDIN_FILENO)
			close(exec_data->fd_in);
		if (exec_data->fd_out != STDOUT_FILENO)
			close(exec_data->fd_out);
	}
	else if (exec_data->i != nbr_cmd - 1 ) // start with  > 1 cmd
	{
		// dprintf(2, "dup 1 cmd\n");
		dup2(exec_data->fd_in, STDIN_FILENO);
		dup2(table->fd_pipe[1], STDOUT_FILENO);
	}
	else if (exec_data->i == nbr_cmd - 1) // end
	{
		// dprintf(2, "last cmd\n");
		// printf("fd_out : %d\n", exec_data->fd_out);
		exec_data->fd_out = STDOUT_FILENO; // for test
		dup2(*fd_tmp_read, STDIN_FILENO);
		dup2(exec_data->fd_out, STDOUT_FILENO);
		if (exec_data->fd_out != STDOUT_FILENO)
			close(exec_data->fd_out);
	}
	else // btw
	{
		// dprintf(2, "btw cmd\n");
		dup2(*fd_tmp_read, STDIN_FILENO);
		dup2(table->fd_pipe[1], STDOUT_FILENO);
	}
}
void ft_initdata_exec(t_list *tb_lst, char **env)
{
	t_table *table;
	int i_cnt = 0;
	table = (t_table *)(tb_lst->data);
	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		table->exec_data.i = i_cnt;
		table->exec_data.pid = 0;
		table->exec_data.fd_in = 0;
		table->exec_data.fd_out = 0;
		table->exec_data.nbr_infile = ft_cnt_infile(tb_lst);
		table->exec_data.nbr_out_append = 0;
		table->exec_data.nbr_heredoc = ft_cnt_heredoc(tb_lst);
		i_cnt++;
		tb_lst = tb_lst->next;
	}
}

void ft_waitpid(t_minishell *ms)
{
	int		i;
	t_list	*tb_lst;

	i = 0;
	tb_lst = ms->tb_lst;
	while (i < ft_lstsize(ms->tb_lst))
	{
		waitpid(ms->pid[i], NULL, 0);
		tb_lst = tb_lst->next;
		i++;
	}
}

int ft_check_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (BUI_CHILD);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (BUI_CHILD);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (BUI_CHILD);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (BUI_PARENT);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (BUI_PARENT);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (BUI_PARENT);
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		if (cmd[1] == NULL)
			return (BUI_CHILD);
		return (BUI_PARENT);
	}
	return (CMD_);
}
void ft_execute(t_minishell *ms, t_list *tb_lst)
{
	int fd_read;
	t_table *table;
	t_data *data_exec;
	t_list *tb_lst_cpy = NULL;
	int		i;

	fd_read = 0;
	tb_lst_cpy = ms->tb_lst;
	i = 0;
	ms->pid = malloc(sizeof(pid_t) * ft_lstsize(ms->tb_lst));
	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		if (ms->nbr_cmd_all > 1 && i != ms->nbr_cmd_all - 1)
		{
			if (pipe(table->fd_pipe) == -1)
				ft_prterr(CANNT_PIPE, "Pipe");
		}
		table->exec_status = ft_check_builtin(table->cmd);
		ms->pid[i] = fork();
		// dprintf(2, "ms->pid[%d] =%d\n", i, ms->pid[i]);
		if (ms->pid[i] == -1)
			ft_prterr(CANNT_FORK, "Fork");
		if (ms->pid[i] == 0)
			branch_child(ms, tb_lst, &fd_read);
		if (ms->pid[i] > 0)
			branch_parent(ms, tb_lst, &fd_read);
		tb_lst = tb_lst->next;
		i++;
	}
	ft_waitpid(ms);
	// ft_prtdict(ms->dict);
	// dprintf(2, "\n");
}
