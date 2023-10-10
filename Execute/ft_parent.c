/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 05:58:25 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/11 00:39:06 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_checkpath(t_dict *dict)
{
	int	found;

	found = 0;
	while (dict)
	{
		if (ft_strcmp(dict->tmp_dict->key, "PATH") == 0)
			found = 1;
		dict = dict->next;
	}
	return (found);
}

void	ft_parent_do_nothing(t_minishell *ms, t_list *tb_lst, int *fd_read)
{
	t_table	*table;

	table = (t_table *)(tb_lst->data);
	if (ms->nbr_cmd_all > 0)
		*fd_read = dup(table->fd_pipe[0]);
	ft_close_pipe(ms, tb_lst);
}

void	ft_parent_builtin(t_minishell *ms, t_list *tb_lst, int *fd_read)
{
	t_table	*table;

	table = (t_table *)(tb_lst->data);
	ft_check_unset(ms);
	ft_getfd(tb_lst);
	*fd_read = dup(table->fd_pipe[0]);
	ft_close_pipe(ms, tb_lst);
	if (table->exec_status == BUI_PARENT)
	{
		if (ft_strcmp(table->cmd[0], "cd") == 0)
			ft_cd(table->cmd, ms);
		if ((ft_strcmp(table->cmd[0], "export") == 0) && table->cmd[1])
			ft_export(table->cmd, &ms->dict);
		if (ft_strcmp(table->cmd[0], "unset") == 0)
			ft_unset(table->cmd, &ms->dict);
		if (ft_strcmp(table->cmd[0], "exit") == 0)
			ft_exit(table->cmd, ms);
	}
}

t_dict	*branch_parent(t_minishell *ms, t_list *tb_lst, int *fd_read)
{
	t_table	*table;

	table = (t_table *)(tb_lst->data);
	if (table->exec_status == BUI_PARENT)
		ft_parent_builtin(ms, tb_lst, fd_read);
	else
		ft_parent_do_nothing(ms, tb_lst, fd_read);
	return (ms->dict);
}
