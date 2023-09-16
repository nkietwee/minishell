/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 02:36:27 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/17 01:28:02 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_heredoc(t_list *table_list, int cnt_heredoc)
{
	t_table *table;
	t_rdr	*rdr;
	char	*tmp;
	int		i;
	int		fd_heredoc;

	i = 0;
	tmp = NULL;
	fd_heredoc = open("tmpfile", O_CREAT | O_TRUNC, 0644);
	while(table_list)
	{
		table = (t_table *)(table_list->data);
		rdr = (t_rdr *)(table->rdr->data);
		rdr->file = ft_strjoinextra(rdr->file, "\n", NONE);
		while (i < cnt_heredoc)
		{
			write(STDOUT_FILENO, "> ", 2);
			tmp = get_next_line(STDIN_FILENO);
			if (ft_strcmp(tmp , rdr->file) == EXIT_SUCCESS)
				break;
			if (i == cnt_heredoc - 1)
				write(fd_heredoc, tmp, ft_strlen(tmp));
			// free(rdr->file);
		}
		i++;
		if (i == cnt_heredoc)
			break;
	}
	// close(fd_heredoc);
	return(fd_heredoc);
}

// int main(int ac, char **av)
// {
// 	// t_data data;
// 	ft_heredoc(ac, av);
// }