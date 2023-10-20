/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:45:34 by ptungbun          #+#    #+#             */
/*   Updated: 2023/10/11 00:00:44 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMINISHELL_H
# define LIBMINISHELL_H

# include <stddef.h>

/*  libft_minisell  */

int	ft_ismetachar(char c);
int	ft_isquote(char c);
int	ft_isvalide_quote(char *str);

#endif
