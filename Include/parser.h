/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:24:48 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/17 00:32:11 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* Common Header  */
# include "libft.h"
# include "libminishell.h"

typedef struct  s_minishell t_minishell;
typedef struct  s_list t_list;


/*  prompt.c  */
char	*prompt(void);

/*  lexer.c  */
int		lexer(char *line, t_minishell *env);

/*  init_minishell.c  */

// t_minishell	init_minishell();

/*  init_command_list.c  */

int		slide_n_decide(t_list *lst, char *line);
int		init_command_list(t_minishell **env, char *line);

/*  grab.c  */

size_t	arg_logic(char *line);
size_t	quote_logic(char *line);
size_t	metachar_logic(char *line);
char	*grab_n_slide(char **line, size_t (*logic)(char *));
void	grab_to_lst(t_list **lst, char **line, int index);

/*  tokenize  */

int	tokenize(t_minishell **env);

/*  quotes_validate.c  */

int	quotes_validate(t_minishell *env);

/*  paser.c  */

int	paser(t_minishell *ms);

/*  get_cmd_to_table.c  */

int	get_cmd_to_table(t_minishell **ms);

/*  get_rdr_to_table.c  */

int	get_rdr_to_table(t_minishell **ms);


#endif