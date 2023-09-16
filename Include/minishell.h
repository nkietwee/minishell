/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:48:46 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/17 01:32:17 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include <unistd.h> //access
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h> //open
# include <readline/readline.h>
# include <readline/history.h>


# include "builtins.h"
# include "color.h"
# include "execute.h"
# include "get_next_line.h"
# include "libft.h"
# include "libminishell.h"
# include "parser.h"

// #define table"ms->table"

/* token and tag_ctrl index define*/

# define EMPTY 0
# define CMD 1
# define ARG 2
# define FPATH 3
# define INFILE 4
# define OUTFILE 5
# define HEREDOC 6
# define PIPE 7
# define APPEND 8

/* tag_ctrl index define*/

# define START 9
# define IFBFCMD 10
# define OFBFCMD 11
# define HDBFCMD 12
# define APBFCMD 13
# define FPBFCMD 14

enum e_prterr
{
	CANNT_PIPE,
	CANNT_FORK,
	CANNT_OPENIN,
	CANNT_OPENOUT,
	PER_DN,
	CANNT_OPEN
};

enum e_typestrjoin
{
	BEFORE,
	AFTER,
	BEFOREANDAFTER,
	NONE
};

enum e_prtexec
{
	ERR_PATH,
	ERR_CMD
};

// enum e_type
// {
// 	HEREDOC,
// 	INFILE,
// 	APPEND,
// 	OUTFILE
// } ;

typedef struct	s_token
{
	int		type;
	char	*str;
}				t_token;

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

typedef struct s_dict_value
{
	char *key;
	char *value;
} t_dict_value;

typedef struct s_dict
{
	t_dict_value *tmp_dict;
	struct s_dict *next;
} t_dict;

typedef struct s_rdr
{
	int		type;
	char	*file;
} t_rdr;

typedef struct s_table
{
	t_list	*rdr; // redirect
	char	**cmd;
} t_table;

typedef struct s_data
{
	pid_t	*pid;
	int		fd_in;
	int		fd_out;
	int		fd_tmp_read;
	int		fd_pipe[2];
	int		nbr_infile;
	int		nbr_out_append;
	int		nbr_cmd;

	int		fd_heredoc;
	int		tmp_ac;
	char	**tmp_av;
	char	**tmp_env;
	char	**path;
} t_data;


typedef struct	s_minishell
{
	t_list	*lst; // lexer
	t_list	*table; // parser
	t_dict	*dict; // env
	t_data	*data; // for execute

} t_minishell;




// typedef struct s_data
// {
// 	// t_cmd *cmd;
// 	int		fd_in; // for last infille
// 	int		fd_heredoc;
// 	int		fd_out; // for last outfile
// 	int		fd_pipe[2];
// 	int		fd_read;
// 	char	**arg;
// 	char	**cmd;
// 	char	**path; // env
// 	char	**tmp_env;
// 	pid_t	*pid; //for fork
// 	int		fd_tmp_read;
// 	int		cnt_cmd;
// 	int		cnt_heredoc;

// 	int		tmp_ac;
// 	char	**tmp_av;
// 	t_dict	**dict;
// } t_data;


#endif