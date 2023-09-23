/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:33:50 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/23 23:54:13 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

typedef struct s_rdr t_rdr;
typedef struct s_data t_data;
typedef struct s_env t_env;
typedef struct s_rdr t_rdr;
typedef struct s_list t_list;
typedef struct s_minishell t_minishell;

void	ft_initdata(t_minishell *ms, char **env);

void	ft_mainexec(t_minishell *ms);

void	ft_execute(t_list *tb_lst);
/* ft_getfile */
void	ft_getfd(t_minishell *main);
int	ft_getfd_in(t_minishell *main);
int	ft_getfd_out(t_minishell *main);
int	ft_cnt_infile(t_list *table_list);
int	ft_cnt_outfile(t_list *table_list);
int	ft_cnt_heredoc(t_list *table_list);

/*ft_cnt_execute*/
void	ft_countexec(t_minishell *ms);
int		ft_cntfile(t_rdr *file);
int		ft_cntcmd(t_list *table_list);

/*ft_check_name*/
int	ft_checkfile(t_list *tb_lst);


void	ft_prterr(int mode);
void	ft_prterrexec(char *str, int errno, int mode);

int	ft_findchar(char *s1, char s2);

/*ft_heredoc*/
int	ft_heredoc(t_list *table_list, int cnt_heredoc);
// void	ft_heredoc(int ac, char **av);
#endif
