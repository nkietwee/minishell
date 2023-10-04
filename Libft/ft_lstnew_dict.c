/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_dict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 02:02:32 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/04 12:36:42 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*ft_lstnew_dict(void *content)
{
	t_dict	*new;

	new = (t_dict *)malloc(sizeof(t_dict));
	if (!new)
		return (NULL);
	new->tmp_dict = content;
	new->next = NULL;
	return (new);
}

// t_dict	*ft_lstnew(void *content)
// {
// 	t_dict	*new;

// 	new = (t_dict *)malloc(sizeof(t_dict));
// 	if (!new)
// 		return (NULL);
// 	new -> content = content;
// 	new -> next = NULL;
// 	return (new);
// }
