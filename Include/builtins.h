/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:57:55 by nkietwee          #+#    #+#             */
/*   Updated: 2023/06/26 00:15:01 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H


enum e_error
{
    PER_DN,
    CANNT_OPEN
    
};

void    ft_echo(char *str);
void    ft_cd(char *str);
void    ft_prterr(int mode, char *cmd, char *str, int err);
void    ft_env(char **env);

#endif