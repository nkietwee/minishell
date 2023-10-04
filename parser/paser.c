/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:52:19 by ptungbun          #+#    #+#             */
/*   Updated: 2023/10/04 12:36:42 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error_exit(t_minishell *ms)
{
	if (ms->err_code == 5)
	{
		dprintf(2, "%s", ERREXPANDVAR);
		ft_lstclear(&ms->tk_lst, &free);
		ms->tk_lst = NULL;
	}
	if (ms->err_code == 6)
		dprintf(2, "%s", ERRCMDTOTABLE);
	if (ms->err_code == 7)
		dprintf(2, "%s", ERRRDRTOTABLE);
	if  (ms->err_code > 5)
		clear_tb_n_tk(ms);
	return (1);
}

int	paser(t_minishell *ms)
{
	if (expand_var(&ms))
		return (print_error_exit(ms));
	if (get_cmd_to_table(&ms))
		return (print_error_exit(ms));
	if (get_rdr_to_table(&ms))
		return (print_error_exit(ms));
	return (0);
}
