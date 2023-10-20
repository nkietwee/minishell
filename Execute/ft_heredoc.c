/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 02:36:27 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/11 00:19:20 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_unlink(t_list	*tb_lst)
{
	t_table	*table;
	t_data	*exec_data;
	t_rdr	*rdr;
	int		i;

	i = 0;
	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		exec_data = (t_data *)(&(table->exec_data));
		while (table->rdr)
		{
			rdr = (t_rdr *)(table->rdr->data);
			if (rdr->type == HEREDOC && i == exec_data->nbr_heredoc - 1)
				unlink(exec_data->filename);
			i++;
			table->rdr = table->rdr->next;
		}
		tb_lst = tb_lst->next;
	}
}

// int	ft_gettxt(t_list *rdr_lst, char *file, int i, int nbr_heredoc)
// {
// 	char	*tmp;
// 	char	*deli;
// 	t_rdr	*rdr;
// 	int		fd_heredoc;

// 	rdr = (t_rdr *)(rdr_lst->data);
// 	deli = ft_strjoinextra(rdr->file, "\n", NONE);
// 	// dprintf
// 	fd_heredoc = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);

// 	return (fd_heredoc);
// }

// int	ft_do_here(t_list *rdr_lst, int nbr_heredoc, char *file)
// {
// 	t_rdr	*rdr;
// 	int		fd_heredoc;
// 	int		i;

// 	i = 0;
// 	fd_heredoc = 0;
// 	while (rdr_lst)
// 	{
// 		rdr = (t_rdr *)(rdr_lst->data);
// 		if (rdr->type == HEREDOC)
// 			fd_heredoc = ft_gettxt(rdr_lst, file, i, nbr_heredoc);
// 		rdr_lst = rdr_lst->next;
// 	}
// 	close (fd_heredoc);
// 	fd_heredoc = open(file, O_RDONLY, 0644);
// 	return (fd_heredoc);
// }

char	*ft_createfile(int round)
{
	char	*file;
	char	*str;

	str = ft_itoa(round);
	file = ft_strjoin("../tmpfile_", str);
	free (str);
	return (file);
}

static void	loop_get_deli(char *deli, int fd_heredoc, int nbr_heredoc, int	*i)
{
	char	*tmp;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		tmp = get_next_line(STDIN_FILENO);
		if (ft_strcmp(tmp, deli) == EXIT_SUCCESS)
		{
			(*i)++;
			break ;
		}
		if (*i == nbr_heredoc - 1)
			write(fd_heredoc, tmp, ft_strlen(tmp));
		if (tmp)
			free(tmp);
	}
}

int	ft_do_here(t_list *rdr_lst, int nbr_heredoc, char *file)
{
	t_rdr	*rdr;
	int		fd_heredoc;
	int		i;
	char	*deli;

	i = 0;
	while (rdr_lst)
	{
		rdr = (t_rdr *)(rdr_lst->data);
		if (rdr->type == HEREDOC)
		{
			deli = ft_strjoinextra(rdr->file, "\n", NONE);
			fd_heredoc = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			loop_get_deli(deli, fd_heredoc, nbr_heredoc, &i);
			free(deli);
		}
		rdr_lst = rdr_lst->next;
	}
	close (fd_heredoc);
	fd_heredoc = open(file, O_RDONLY, 0644);
	return (fd_heredoc);
}

int	ft_main_heredoc(t_list *tb_lst)
{
	t_table	*table;
	t_data	*exec_data;
	int		round;

	round = 0;
	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		exec_data = (t_data *)(&(table->exec_data));
		exec_data->nbr_heredoc = ft_cnt_heredoc(tb_lst);
		exec_data->filename = ft_createfile(round);
		exec_data->fd_heredoc = ft_do_here(table->rdr, \
			exec_data->nbr_heredoc, exec_data->filename);
		round++;
		tb_lst = tb_lst->next;
	}
	return (0);
}
