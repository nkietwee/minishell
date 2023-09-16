/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 01:24:09 by ptungbun          #+#    #+#             */
/*   Updated: 2023/09/17 02:30:49 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	arg_logic(char *line)
{
	size_t	size;

	size = 0;
	while(!ft_isspace(line[size]) && !ft_ismetachar(line[size]) && line[size])
		size++;
	return(size);
}

size_t	quote_logic(char *line)
{
	size_t		size;
	char	quote;

	quote = line[0];
	size = 1;
	while(line[size] != quote && !ft_ismetachar(line[size]) && line[size])
		size++;
	return(size + 1);
}

size_t	metachar_logic(char *line)
{
	char	meta_c;

	meta_c = line[0];
	if (line[1] != meta_c)
		return (1);
	else if (line[1] == meta_c)
		return (2);
	return (0);
}

char	*grab_n_slide(char **line, size_t (*logic)(char *))
{
	size_t	size;
	char	*str;

	size = logic(*line);
	if (size > 0)
		str = ft_substr(*line, 0, size);
	while(size > 0)
	{
		(*line)++;
		size--;
	}
	while(ft_isspace(*(*line)))
		(*line)++;
	return (str);
}

void	grab_to_lst(t_list **lst, char **line, int index)
{
	t_list	*new;
	t_token	*token;

	new = ft_lstnew(malloc(sizeof(t_token)));
	token = new->data;
	if (index == 0)
	{
		token->str = grab_n_slide(line, &arg_logic);
		*lst = new;
		return ;
	}
	if (index == 1)
		token->str = grab_n_slide(line, &arg_logic);
	if (index == 2)
		token->str = grab_n_slide(line, &quote_logic);
	if (index == 3)
		token->str = grab_n_slide(line, &metachar_logic);
	if (index != 0)
		ft_lstadd_back(lst, new);
}
