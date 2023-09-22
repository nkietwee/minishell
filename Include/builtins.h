/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 02:58:41 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/17 15:26:16 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUIILTINS_H
# define BUIILTINS_H

// typedef struct s_export t_export;
typedef struct s_data t_data;
typedef struct s_dict t_dict;
typedef struct s_dict_value t_dict_value;

void	ft_buildin(char **av, t_data *data, char **env);
// void	ft_initdata(t_data *data, char **env);

/*cnt_builtin*/
int		ft_cntstr(char **str);
int		ft_cntdict(t_dict **dict);
int		ft_cnt_bf_equal(char *str);
int		ft_cnt_at_equal(char *str);
int		ft_cntdict_export(t_dict_value **dict);

int		ft_findstr(char *str, char *find, int len);

/*cd*/
void	ft_cd(char **cmd);

/*pwd*/
void	ft_pwd(void);

/*echo*/
void	ft_echo(char **str);

/* env */
t_dict *ft_getenv(char **env);
t_dict_value **ft_getvalue_env(char **env);

/*export*/
// t_dict	*ft_export(char **ft_env);
t_dict	*ft_export(char **av, char **env);
void	ft_printvalue_ep(char **env);
void	ft_lstascend(t_dict *dict);
void	ft_swap(t_dict *dict);
t_dict	*ft_addvalueexport(char **av, char **env);

/*env*/
void	ft_env(t_data *data);

/*prtlinklist*/
void	ft_prtdict(t_dict	*dict);
void	ft_prtdict_value(t_dict_value	**tmp_value);


/*prt_err*/
void	ft_prterr_builtins(int mode, char *cmd, char *str, int err);
void	ft_prterr_builtins(int mode, char *cmd, char *str, int err);

/*free*/
void	ft_freedict(t_dict **dict);
#endif