/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:26:45 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/01 14:59:54 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// /* left loop in case it many pipe (It have outfile?)*/
// void	ft_dup2(int i, int j, t_data *data)
// {
// 	// printf("ft_dup2\n");
// 	if (i == 0 && data->nbr_cmd == 1) // start with 1 cmd
// 	{
// 		printf("dup only 1 cmd\n");
// 		// printf("fd_in : %d\n" , data->fd_in);
// 		dup2(data->fd_in, STDIN_FILENO);
// 		dup2(data->fd_out, STDOUT_FILENO);
// 	}
// 	else if (i == 0 && data->nbr_cmd != 1) // start with  > 1 cmd
// 	{
// 		// printf("dup 1 cmd\n");
// 		dup2(data->fd_in, STDIN_FILENO);
// 		dup2(data->fd_pipe[1], STDOUT_FILENO);
// 	}
// 	else if (i == data->nbr_cmd - 1) // end
// 	{
// 		// printf("last cmd\n");
// 		// printf("fd_out : %d\n", data->fd_out);
// 		dup2(data->fd_tmp_read, STDIN_FILENO);
// 		dup2(data->fd_out, STDOUT_FILENO);
// 	}
// 	else //btw
// 	{
// 		printf("btw cmd\n");
// 		dup2(data->fd_tmp_read, STDIN_FILENO);
// 		dup2(data->fd_pipe[1], STDOUT_FILENO);
// 	}
// }

int ft_check_buildin(char **cmd)
{
	/*
// echo
// cd
// pwd
export
unset
// env
exit
*/
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (EXIT_SUCCESS);
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (EXIT_SUCCESS);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (EXIT_SUCCESS);
	if (ft_strcmp(cmd[0], "export") == 0)
		return (EXIT_SUCCESS);
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (EXIT_SUCCESS);
	if (ft_strcmp(cmd[0], "env") == 0)
		return (EXIT_SUCCESS);
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);

	// if (ft_findstr(cmd[0], "export", 6) == EXIT_SUCCESS)
	// 	return (EXIT_SUCCESS);
	// else if (ft_findstr(cmd[0], "cd", 2) == EXIT_SUCCESS)
	// 	return (EXIT_SUCCESS);
	// else if (ft_findstr(cmd[0], "unset", 5) == EXIT_SUCCESS)
	// 	return (EXIT_SUCCESS);
	// else if (ft_findstr(cmd[0], "exit", 4) == EXIT_SUCCESS)
	// 	return (EXIT_SUCCESS);
	// return (EXIT_FAILURE);
}

/*close fd after dup */
void ft_dup2(int i, t_list *tb_lst, int *fd_tmp_read, int nbr_cmd)
{
	t_table *table;
	t_data *exec_data;

	table = (t_table *)(tb_lst->data);
	exec_data = (t_data *)(&(table->exec_data));
	// dprintf(2, "i : %d\n", i);
	// dprintf(2, "nbr_cmd : %d\n", nbr_cmd);

	if (i == 0 && nbr_cmd == 1) // for 1 cmd
	{
		// dprintf(2, "fd_out_dup2 : %d\n", exec_data->fd_out);
		dup2(exec_data->fd_in, STDIN_FILENO);
		dup2(exec_data->fd_out, STDOUT_FILENO);
		// dprintf(2, "finish_dup\n");

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
		dup2(*fd_tmp_read, STDIN_FILENO);
		dup2(exec_data->fd_out, STDOUT_FILENO);
	}
	else //btw
	{
		// printf("btw cmd\n");
		dup2(*fd_tmp_read, STDIN_FILENO);
		dup2(exec_data->fd_pipe[1], STDOUT_FILENO);
	}
}

void ft_initdata_exec(t_list *tb_lst)
{
	t_table *table;
	int	i_cnt = 0;
	table = (t_table *)(tb_lst->data);
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
		table->exec_data.nbr_out_append = ft_cnt_outfile(tb_lst);
		table->exec_data.nbr_heredoc = ft_cnt_heredoc(tb_lst);
		table->exec_data.fd_heredoc = 0;
		i_cnt++;
		tb_lst = tb_lst->next;
	}
	// dprintf(2, "ft_initdata_exec\n");
}

void ft_waitpid(t_list *tb_lst_cpy)
{
	t_table *table_cpy;
	t_data data_exec_cpy;

	while (tb_lst_cpy)
	{
		table_cpy = (t_table *)(tb_lst_cpy->data);
		data_exec_cpy = (table_cpy->exec_data) ;
		// dprintf(2, "id[%d] in wait : %d\n", table_cpy->i, data_exec_cpy.pid);
		waitpid(data_exec_cpy.pid, NULL, 0);
		tb_lst_cpy = tb_lst_cpy->next;
	}
}

void ft_execute(t_list *tb_lst, char **env, int nbr_cmd)
{
	int fd_tmp_read;
	t_table *table;
	t_data *data_exec;
	t_list *tb_lst_cpy = NULL;

	fd_tmp_read = 0;
	// ft_initdata_exec(tb_lst);
	// printf("cnt_cmd : %d\n", nbr_cmd);
	tb_lst_cpy = tb_lst;
	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		data_exec = (t_data *)(&(table->exec_data));
		if (nbr_cmd > 1)
		{
			if (pipe(data_exec->fd_pipe) == -1)
				ft_prterr(CANNT_PIPE, "test");
		}
		if (ft_check_buildin(table->cmd) == EXIT_FAILURE)
			data_exec->pid = fork();
		if (data_exec->pid == -1)
			ft_prterr(CANNT_FORK, "test");
		if (data_exec->pid == 0 && ft_check_buildin(table->cmd) == EXIT_FAILURE)
			ft_child(tb_lst, nbr_cmd, env, &fd_tmp_read);
		if (data_exec->pid > 0)
			ft_parent(tb_lst, &fd_tmp_read, nbr_cmd, env);
		tb_lst = tb_lst->next;
	}
	// close(data_exec->fd_out);
	// close(data_exec->fd_in);
	ft_waitpid(tb_lst_cpy);
}

// void	ft_execute(t_minishell *ms)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 2;
// 	t_table *table;

// 	printf("ft_execute\n");
// 	ms->data.nbr_cmd = ft_cntcmd(ms->tb_lst);
// 	// ft_
// 	printf("nbr_cmd : %d\n" , ms->data.nbr_cmd);
// 	ms->data.pid = malloc(sizeof(pid_t) * ms->data.nbr_cmd);
// 	if (!ms->data.pid)
// 		return ;
// 	// printf("before_getfd\n");
// 	// exit(0);
// 	i = 0;
// 	while(i < ms->data.nbr_cmd)
// 	{
// 		// ft_getfd(((t_table *)(ms->tb_lst->data))->data);
// 		printf("in while\n");
// 		if (pipe(ms->data.fd_pipe)== -1)
// 			ft_prterr(CANNT_PIPE);
// 		ms->data.pid[i] = fork();
// 		if (ms->data.pid[i] == -1)
// 			ft_prterr(CANNT_FORK);
// 		else if (ms->data.pid[i] == 0)
// 			ft_child(i, &ms->data, j);
// 		else
// 			ft_parent(&ms->data);
// 		i++;
// 		j++;
// 	}
// 	int k = 0;
// 	while(k < ms->data.nbr_cmd)
// 	{
// 		waitpid(ms->data.pid[k], NULL, 0);
// 		k++;
// 	}
// }
