/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:52:19 by ptungbun          #+#    #+#             */
/*   Updated: 2023/10/10 22:45:24 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	print_error_exit(t_minishell *ms)
{
	if (ms->err_code == 5)
	{
		dprintf(2, "%s", ERREXPANDVAR);
		ft_lstclear(&ms->tk_lst, &free);
		ms->tk_lst = NULL;
	}
	if (ms->err_code == 6)
		printf("%s", ERRCMDTOTABLE);
	if (ms->err_code == 7)
		printf("%s", ERRRDRTOTABLE);
	if (ms->err_code == 8)
		printf("%s", ERRD);
	if (ms->err_code == 9)
		printf("%s", ERRDD);
	if (ms->err_code > 5)
		clear_tb_n_tk(ms);
	return (1);
}

static int	validate_cmd(t_minishell *ms)
{
	t_list	*tb_lst;
	t_table	*table;
	char	**cmd;

	tb_lst = ms->tb_lst;
	while (tb_lst)
	{
		table = tb_lst->data;
		if (table->cmd[0])
		{
			cmd = table->cmd;
			if (ft_strcmp(cmd[0], ".") == 0)
				return (exit_err(ms, 8));
			if (ft_strcmp(cmd[0], "..") == 0)
				return (exit_err(ms, 9));
		}
		tb_lst = tb_lst->next;
	}
	return (0);
}

int	paser(t_minishell *ms)
{
	if (expand_var(&ms))
		return (print_error_exit(ms));
	if (get_cmd_to_table(&ms))
		return (print_error_exit(ms));
	if (get_rdr_to_table(&ms))
		return (print_error_exit(ms));
	if (validate_cmd(ms))
		return (print_error_exit(ms));
	return (0);
}
