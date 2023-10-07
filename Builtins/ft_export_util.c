/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:03:35 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/08 00:31:12 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_find_repeat(char *find, t_dict *dict)
{
	while (dict)
	{
		if (ft_strcmp(dict->tmp_dict->key, find) == 0)
			return (EXIT_SUCCESS);
		dict = dict->next;
	}
	return (EXIT_FAILURE);
}

void	ft_instead_value(char **find, t_dict *dict)
{
	int	i;

	i = 0;
	while (dict)
	{
		if (ft_strcmp(dict->tmp_dict->key, find[0]) == 0)
		{
			free (dict->tmp_dict->value);
			if (find && find[1])
				dict->tmp_dict->value = ft_strdup(find[1]);
			else
				dict->tmp_dict->value = NULL;
		}
		dict = dict->next;
	}
}

void	ft_dbfree(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_cnt_repeat(char **str, t_dict *dict)
{
	int		i;
	int		repeat;
	char	**sp;

	i = 0;
	repeat = 0;
	while (str[i])
	{
		sp = ft_split(str[i], '=');
		if (ft_find_repeat(sp[0], dict) == EXIT_SUCCESS)
			repeat++;
		ft_dbfree(sp);
		i++;
	}
	return (repeat);
}

//str is arg that wanted to add at last arg from env
// t_dict_value	**ft_get_value(char **str, t_dict *dict)
// {
// 	int	len;
// 	t_dict_value **tmp;
// 	char	**sp_2;
// 	int	i;
// 	int repeat;

// 	repeat = ft_cnt_repeat(str, dict);
// 	i = 0;
// 	len = ft_cntstr(str) - repeat  - 1;
// 	tmp = malloc(sizeof(t_dict_value *) * (len + 1));
// 	if (!tmp)
// 		return (NULL);
// 	int t = 0;
// 	while (str[i])
// 	{
// 		tmp[i] = malloc(sizeof(t_dict_value ));
// 		sp_2 = ft_split(str[i], '=');
// 		if (sp_2 == NULL)
// 			return (NULL);
// 		if (ft_find_repeat(sp_2[0], dict) == EXIT_SUCCESS && sp_2[0]) // repeat value
// 		{
// 			ft_instead_value(sp_2, dict);
// 			t = 1;
// 		}
// 		if (t == 0)
// 		{
// 			if (sp_2[0])
// 				tmp[i]->key = ft_strdup(sp_2[0]);
// 			else
// 				tmp[i]->key = ft_strdup("");
// 			if (sp_2[1])
// 				tmp[i]->value = ft_strdup(sp_2[1]);
// 			else
// 				tmp[i]->value = NULL;
// 			i++;
// 		}
// 		t = 0;
// 		i++;
// 		ft_dbfree(sp_2);
// 	}
// 	tmp[i] = NULL;
// 	return (tmp);
// }

/*av instead value that it want to attach with last arg*/

int		key_scan(char *str, t_dict *dict)
{
	char	*key;
	int		i;

	i = 0;
	while (dict)
	{
		key = dict->tmp_dict->key;
		if (ft_strcmp(key, str) == 0)
			return(i);
		dict = dict->next;
		i++;
	}
	return (0);
}

t_dict	*pick_dict(t_dict *dict, int index)
{
	while(index < 0)
	{
		index--;
		dict = dict->next;
	}
	return (dict);
}

void	ft_addvalueexport(char **av, t_dict *dict)
{
	int		i;
	int		index;
	char	**sp;
	t_dict	*new_dict;

	i = 1;
	while (av[i])
	{
		index = key_scan(sp[0], dict);
		sp = ft_split(av[i], '=');
		if (index == 0)
		{
			new_dict = ft_lstnew_dict(malloc(sizeof(t_dict)));
			new_dict->tmp_dict->key = ft_strdup(sp[0]);
			new_dict->tmp_dict->value = ft_strdup(sp[1]);
			ft_lstadd_back_dict(&dict, new_dict);
		}
		else
		{
			new_dict = pick_dict(dict, index);
			free(new_dict->tmp_dict->value);
			new_dict->tmp_dict->value = ft_strdup(sp[1]);
		}
		ft_freesplite(sp);
		i++;
	}
}
