/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:26:21 by ptungbun          #+#    #+#             */
/*   Updated: 2023/09/17 15:00:07 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	trim_quote(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while(str[i])
// 	{
// 		str[i] = str[i + 1];
// 		i++;
// 	}
// 	str[i - 2] = '\0';
// }

int	quotes_validate(t_minishell *env)
{
	t_list	*lst;
	char	*str;

	lst = env->tk_lst;
	while (lst)
	{
		str = ((t_token *)(lst->data))->str;
		if (ft_isquote(*str))
		{
			if (!ft_isvalide_quote(str, str[0]))
				return (2);
		}
		lst = lst->next;
	}
	 return (0);
}
