/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:33:50 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/11 00:27:12 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

typedef struct s_rdr		t_rdr;
typedef struct s_data		t_data;
typedef struct s_env		t_env;
typedef struct s_rdr		t_rdr;
typedef struct s_list		t_list;
typedef struct s_table		t_table;
typedef struct s_minishell	t_minishell;

void	ft_prt_type(int type);
void	ft_execvecmd(char **cmd, char **path, t_minishell *ms);

void	ft_initdata(t_minishell *ms, char **env);
t_dict	*branch_parent(t_minishell *ms, t_list *tb_lst, int *fd_read);
void	ft_mainexec(t_minishell *ms);
char	**ft_findpath(char **env);
void	ft_execute(t_minishell *ms, t_list *tb_lst);
void	ft_openpipe(t_minishell *ms, t_table *table, int i);
int		ft_check_buildin(char **cmd);
void	ft_prt_type(int type);
void	ft_initdata_exec(t_list *tb_lst);

void	ft_unlink(t_list	*tb_lst);
/* ft_getfile */
void	ft_getfd(t_list *tb_lst);
int		ft_getfd_in(t_list *tb_lst);
int		ft_getfd_out(t_list *tb_lst);
int		ft_cnt_infile(t_list *table_list);
int		ft_cnt_outfile(t_list *table_list);
int		ft_cnt_heredoc(t_list *table_list);

/*ft_cnt_execute*/
int		ft_cntfile(t_rdr *file);
int		ft_cntcmd(t_list *table_list);
void	ft_countexec(t_list *tb_lst);

int		ft_checkpath(t_dict *dict);

/*ft_check_name*/
int		ft_checkfile(t_list *tb_lst);
void	ft_dup2(t_list *tb_lst, int *fd_tmp_read, int nbr_cmd);

/*ft_execve*/
void	ft_export(char **cmd, t_dict **dict);
void	ft_execvepath(char **path, t_minishell *ms);
void	ft_parent(t_list *tb_lst, int *fd_tmp_read, int nbr_cmd, char **env);
void	branch_child(t_minishell *ms, t_list *tb_lst, int *fd_tmp_read);

/*ft_execute*/
int		ft_check_builtin(char **cmd);
void	ft_waitpid(t_minishell *ms);
void	ft_close_pipe(t_minishell *ms, t_list *tb_lst);

void	ft_prterr(int mode, char *txt);
void	ft_prterrexec(char *str, int mode);

int		ft_findchar(char *s1, char s2);

/*ft_heredoc*/
int		ft_main_heredoc(t_list *tb_lst);

void	ft_heredoc(t_list *tb_lst);

/*ft_unset*/

#endif
