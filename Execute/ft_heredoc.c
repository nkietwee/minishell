/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:36:05 by nkietwee          #+#    #+#             */
/*   Updated: 2023/07/02 20:06:25 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Include/minishell.h"

//deli -> delimeter
// void    ft_heredoc(char **deli)
// {   
//     char    *input;
//     char    *tmp=NULL;
//     char    **deli;
//     int     i = 0;
    
//     while(1)
//     {
//         input = readline("\x1B[34m]""Enter a line of text: ""\033[0m");
//         if (!input)
//             return (0);
//         int fd = open("a.txt" , O_CREAT | O_RDWR | O_APPEND , 0644);

//         if (ft_strcmp(deli[0], "<<") == EXIT_SUCCESS)
//         {
//             i = 1;
//             while (1)
//             {
//                 while (deli[i])
//                 {      
//                     write(1, "> ", 2);
//                     tmp = get_next_line(STDIN_FILENO);
//                     if (ft_strcmp(tmp ,deli[i]) == EXIT_SUCCESS)
//                         break;
//                     ft_putstr(tmp);
//                     int len = ft_strlen(tmp); // -1 because - newline
//                     write(fd, tmp, len);
//                     free (tmp); 
//                 }
//                 i++;
//                 if (deli[i] == NULL)
//                     break;
//             }
//         }
//         close(fd);
//     }
//     free(input);
//     return 0;
// }
