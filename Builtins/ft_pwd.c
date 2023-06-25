/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:13:15 by nkietwee          #+#    #+#             */
/*   Updated: 2023/06/24 21:26:17 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Include/minishell.h"

void    ft_pwd(void)
{
    char path[128];
    // char *tmp ;
    getcwd(path, 128);
    printf("%s\n", path);
    // printf("tmp : %s\n", tmp);
    // exit ()
}