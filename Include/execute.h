/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:33:50 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/07 16:14:36 by pnamwayk         ###   ########.fr       */
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
char	**ft_findpath(char **env);
void	ft_execute(t_minishell *ms, t_list *tb_lst);
// void ft_execute(t_list *tb_lst, t_dict *dict, int nbr_cmd);
// void	ft_initdata_exec(t_list *tb_lst);
void	ft_initdata_exec(t_list *tb_lst, char **env);
int		ft_check_builtin(char **cmd);
void	ft_prt_type(int type);
/* ft_getfile */
void	ft_getfd(t_minishell *ms, t_list *tb_lst);
int	ft_getfd_in(t_list *tb_lst);
int	ft_getfd_out(t_list *tb_lst);
int	ft_cnt_infile(t_list *table_list);
int	ft_cnt_outfile(t_list *table_list);
int	ft_cnt_heredoc(t_list *table_list);

/*ft_cnt_execute*/
int		ft_cntfile(t_rdr *file);
int		ft_cntcmd(t_list *table_list);
void	ft_countexec(t_list *tb_lst);

/*ft_check_name*/
int	ft_checkfile(t_list *tb_lst);

/*ft_execve*/
void	ft_execvecmd(char **cmd, char **path, char **tmp_env);
void	ft_execvepath(char **path, char **tmp_env);
void ft_close_pipe(t_minishell *ms, t_list *tb_lst);


void	ft_parent_builtin(t_minishell *ms, t_list *tb_lst);
void	ft_parent_do_nothing(t_minishell *ms, t_list *tb_lst);

void	ft_child_exve(t_minishell *ms, t_list *tb_lst);
void	ft_child_builtin(t_minishell *ms, t_list *tb_lst);
void	ft_child_do_nothing(t_minishell *ms, t_list *tb_lst);

// void	ft_child(t_list *tb_lst, int nbr_cmd, t_dict *dict, int *table->fd_tmp);
// void	ft_parent(t_list *tb_lst,int *table->fd_tmp, int nbr_cmd , t_dict *dict);
/*ft_execute*/
void ft_dup2(t_minishell *ms, t_list *tb_lst);
int		ft_check_builtin(char **cmd);
void ft_waitpid(t_minishell *ms, t_list *tb_lst);

void	ft_prterr(int mode, char *txt);
// void	ft_prterr(int mode);
void	ft_prterrexec(char *str, int errno, int mode);

int	ft_findchar(char *s1, char s2);

/*ft_heredoc*/
void	ft_heredoc(t_list *table_list);

/*ft_unset*/
// void	ft_unset(char **cmd, t_dict *dict);

// void	ft_heredoc(int ac, char **av);
#endif
