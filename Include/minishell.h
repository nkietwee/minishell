/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:34:03 by nkietwee          #+#    #+#             */
/*   Updated: 2023/07/02 20:05:45 by nkietwee         ###   ########.fr       */
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


typedef struct s_data
{
    char    **infile; // loop open infile;
    char    **outfile; // loop open outfile
    char    **append; // loop open outfile
    char    **heredoc; // delimeter for heredoc
    int     fd_in; // for last infille
    int     fd_out; // for last outfile
    char    **arg;
    char    **cmd;
     
} t_data;

#endif