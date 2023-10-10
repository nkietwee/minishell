/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:24:21 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/10 15:57:59 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_name_file(char	*file)
{
	if ((file[0] >= 'A' && file[0] <= 'Z') || \
	(file[0] >= 'a' && file[0] <= 'z') || \
	(file[0] >= '0' && file[0] <= '9'))
		return (EXIT_SUCCESS);
	else
	{
		ft_putstr_fd("bash: syntax error near unexpected token ", 2);
		ft_putstr_fd("'", 2);
		ft_putchar_fd(file[0], 2);
		ft_putstr_fd("'", 2);
	}
	return (EXIT_FAILURE);
}

int	ft_checkfile(t_list *tb_lst)
{
	t_table	*table;
	t_list	*rdr_lst;
	t_rdr	*rdr;

	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		rdr_lst = (table->rdr);
		while (rdr_lst)
		{
			rdr = (t_rdr *)(rdr_lst->data);
			if (rdr->type == INFILE || rdr->type == OUTFILE \
			|| rdr->type == APPEND)
			{
				if (ft_check_name_file(rdr->file) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			rdr_lst = rdr_lst->next;
		}
		tb_lst = tb_lst->next;
	}
	return (EXIT_SUCCESS);
}
