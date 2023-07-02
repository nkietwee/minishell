/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:13:15 by nkietwee          #+#    #+#             */
/*   Updated: 2023/06/28 00:59:40 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Include/minishell.h"

// void    ft_pwd(void)
// {
//     char path[128];
//     char *tmp ;
    
//     tmp = getcwd(path, 128);
//     if (!tmp)
//         return ;
//     printf("%s\n", path);
// }

void    ft_pwd(void)
{
    char *path;
    
    path = getcwd(NULL, 0);
    if (!path)
        return ;
    printf("%s\n", path);
    free (path); //  path malloc
}