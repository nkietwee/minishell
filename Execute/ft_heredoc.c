/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 02:36:27 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/23 20:10:42 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_prt_type(int type)
{
	if (type == EMPTY)
		printf("EMPTY\n");
	else if (type == CMD)
		printf("CMD\n");
	else if (type == ARG)
		printf("ARG\n");
	else if (type == FPATH)
		printf("FPATH\n");
	else if (type == INFILE)
		printf("INFILE\n");
	else if (type == OUTFILE)
		printf("OUTFILE\n");
	else if (type == HEREDOC)
		printf("HEREDOC\n");
	else if (type == PIPE)
		printf("PIPE\n");
	else if (type == APPEND)
		printf("APPEND\n");

}
void	ft_prt_heredoc(t_list *tb_list)
{
	t_table *table;
	t_rdr	*rdr;
	t_list *rdr_lst;

	// printf("Entry ft_prt_heredoc\n");
	while (tb_list)
	{
		table = (t_table *)(tb_list->data);
		rdr_lst = table->rdr;
		while (rdr_lst)
		{
			rdr = (t_rdr *)(rdr_lst->data);
			if (rdr->type == HEREDOC)
			{
				// ft_prt_type(rdr->type);
				printf("heredoc__ : %s\n", rdr->file);
			}
			rdr_lst = rdr_lst->next;
		}
		tb_list = tb_list->next;
	}
}

int	ft_heredoc(t_list *tb_lst, int nbr_heredoc)
{
	t_table *table;
	t_list	*rdr_lst;
	t_rdr	*rdr;
	char	*tmp;
	int		fd_heredoc;
	int		i;

	i = 0;
	ft_prt_heredoc(tb_lst);
	// fd_heredoc = open("tmpfile", O_CREAT | O_RDWR | O_TRUNC, 0644);
	// printf("fd_ : %d\n", fd_heredoc);
	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		rdr_lst = table->rdr;
		while (rdr_lst)
		{
			rdr = (t_rdr *)(rdr_lst->data);
			rdr->file = ft_strjoinextra(rdr->file, "\n", NONE);
			while (1)
			{
				write(STDOUT_FILENO, "> ", 2);
				tmp = get_next_line(STDIN_FILENO);
				if (ft_strcmp(tmp, rdr->file) == EXIT_SUCCESS)
				{
					i++;
					if (i == nbr_heredoc)
						return (fd_heredoc);
					break;
				}
				// printf("i : %d , nbr_heredoc : %d\n", i, nbr_heredoc);
				if (i == nbr_heredoc - 1)
					write(fd_heredoc, tmp, ft_strlen(tmp));
			}
			rdr_lst = rdr_lst->next;
		}
		tb_lst = tb_lst->next;
	}
	// close (fd_heredoc);
	return (0);
	// return (fd_heredoc);
}

// int main(int ac, char **av)
// {
// 	// t_data data;
// 	ft_heredoc(ac, av);
// }