/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:26:45 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/24 01:15:14 by nkietwee         ###   ########.fr       */
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

// void	ft_execvecmd(char **cmd, char **path, char **tmp_env)
// {
// 	int		i;
// 	char	*path_exec;

// 	i = 0;
// 	if (!cmd)
// 		return ;
// 	while (path[i])
// 	{
// 		path_exec = ft_strjoinextra(path[i], cmd[0], NONE);
// 		if (access(path_exec, F_OK) == EXIT_SUCCESS)
// 		{
// 			execve(path_exec, cmd, tmp_env);
// 		}
// 		free(path_exec);
// 		i++;
// 	}
// 	if (path[i] == NULL)
// 		ft_prterrexec(cmd[0], 1, ERR_CMD);
// }


// void	ft_execvepath(char **path, char **tmp_env)
// {
// 	// printf("Entry : execvepath\n");
// 	if (access(path[0], F_OK | X_OK) == -1)
// 	{
// 		ft_prterrexec(path[0], 1, ERR_PATH);
// 		printf("not access\n");
// 		// ft_dbfree((void **)path); // ??
// 	}
// 	else
// 	{
// 		// printf("path\n");
// 		execve(path[0], path, tmp_env);
// 	}
// }

// void	ft_parent(t_data *data)
// {
// 	data->fd_tmp_read = dup(data->fd_pipe[0]); // another process can read from previos process
// 	// printf("tmp_read : %d\n" , data->fd_tmp_read);
// 	close(data->fd_pipe[0]);
// 	close(data->fd_pipe[1]);

// 	// export
// 	// cd
// 	// unset
// 	// exit
// }

// int	ft_check_buildin(char **cmd)
// {
// 	if (ft_findstr(cmd[0], "export", 6) == EXIT_SUCCESS)
// 		return (EXIT_SUCCESS);
// 	else if (ft_findstr(cmd[0], "cd", 2) == EXIT_SUCCESS)
// 		return (EXIT_SUCCESS);
// 	else if (ft_findstr(cmd[0], "unset", 5) == EXIT_SUCCESS)
// 		return (EXIT_SUCCESS);
// 	else if (ft_findstr(cmd[0], "exit", 4) == EXIT_SUCCESS)
// 		return (EXIT_SUCCESS);
// 	return (EXIT_FAILURE);
// }

// void	ft_child(int i, t_data *data, int j)
// {
// 	char **cmd;

// 	ft_dup2(i, j, data);
// 	close(data->fd_pipe[0]);
// 	close(data->fd_pipe[1]);
// 	cmd = ft_split(data->tmp_av[j], ' ');
// 	printf("cmd_child : %s\n", cmd[0]);
// 	ft_check_buildin(cmd);
// 	if (ft_findchar(cmd[0], '/') == EXIT_SUCCESS) // cmd or av4
// 		ft_execvepath(cmd, data->tmp_env);
// 	else
// 		ft_execvecmd(cmd, data->path, data->tmp_env);
// }

void	ft_parent(t_list *tb_lst)
{


}

void	ft_child(t_list *tb_lst)
{


}

void	ft_initdata_exec(t_list *tb_lst)
{
	t_table	*table;

	while (tb_lst)
	{
		table =  (t_table *)(tb_lst->data);
		table->exec_data.pid = 0;
		table->exec_data.fd_in = 0;
		table->exec_data.fd_out = 0;
		table->exec_data.fd_tmp_read = 0;
		table->exec_data.fd_pipe[0] = 0;
		table->exec_data.fd_pipe[1] = 0;
		table->exec_data.nbr_infile = 0;
		table->exec_data.nbr_out_append = 0;
		table->exec_data.nbr_cmd = 0;
		table->exec_data.nbr_heredoc = 0;
		table->exec_data.fd_heredoc = 0;
		tb_lst = tb_lst->next;
	}

}

void	ft_waitpid(t_list *tb_lst_cpy)
{
	t_table *table_cpy;
	t_data	data_exec_cpy;

	while (tb_lst_cpy)
	{
		table_cpy = (t_table *)(tb_lst_cpy->data);
		data_exec_cpy = (table_cpy->exec_data);
		waitpid(data_exec_cpy.pid , NULL, 0);
		tb_lst_cpy = tb_lst_cpy->next;
	}

}

void	ft_execute(t_list *tb_lst)
{
	int	nbr_cmd;
	int	i;
	int	j;
	t_table *table;
	// t_table *table_cpy;
	t_data data_exec;
	t_list	*tb_lst_cpy;

	nbr_cmd = ft_lstsize(tb_lst);
	i = 0;
	// printf("nbr_ : %d\n" , nbr);
	printf("ft_execute\n");
	ft_initdata_exec(tb_lst);
	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		data_exec = (t_data )(table->exec_data);
		if (pipe(data_exec.fd_pipe) == -1)
			ft_prterr(CANNT_PIPE);
		data_exec.pid = fork();
		if (data_exec.pid == -1)
			ft_prterr(CANNT_FORK);
		else if (data_exec.pid == 0)
			ft_child(tb_lst);
		else
			ft_parent(tb_lst);
		tb_lst = tb_lst->next;
		i++;
		j = 0;
		ft_waitpid(tb_lst_cpy);
		tb_lst = tb_lst->next;
	}
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


