/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:34:03 by nkietwee          #+#    #+#             */
/*   Updated: 2023/07/06 19:54:39 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include "../Get_next_line/get_next_line.h"
// # include "../Include/execute.h"
# include "execute.h"
# include "builtins.h"
# include "color.h"


# include <unistd.h> // read ,chdir 
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h> // open
# include <errno.h> //errno

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h> 

enum e_type
{
    HEREDOC,
    INFILE,
    APPEND,
    OUTFILE
} ;


typedef struct s_rdr
{
    enum e_type type;
    // int     type;
    char    *file; // 
    int     index; // for loop open file 
} t_rdr ;

typedef struct s_data
{
    t_rdr   **in_here; 
    t_rdr   **out_append;
    int     fd_in; // for last infille
    int     fd_out; // for last outfile
    char    **arg;
    char    **cmd;
     
} t_data;

#endif