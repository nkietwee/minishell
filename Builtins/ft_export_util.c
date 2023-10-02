/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:03:35 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/02 05:56:54 by nkietwee         ###   ########.fr       */
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
			// if (dict->tmp_dict->value)
			free (dict->tmp_dict->value);
			// dprintf(2, "find[1] : %s\n" , find[1]);
			// if (find && find[1])
			dict->tmp_dict->value = ft_strdup(find[1]);
		}
		dict = dict->next;
	}
}

void	ft_lstinsert_node(t_dict **dict, char **key)
{
	int	i;

	i = 0;

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
		// printf("str : %s\n", str[i]);
		sp = ft_split(str[i], '=');
		if (ft_find_repeat(sp[0], dict) == EXIT_SUCCESS)
			repeat++;
		ft_dbfree(sp);
		i++;
	}
	return (repeat);
}

//str is arg that wanted to add at last arg from env
t_dict_value **ft_get_value(char **str, t_dict *dict)
{
	int	len;
	t_dict_value **tmp;
	char	**sp_2;
	int	i;
	int	j;
	int repeat;

	i = 1;
	repeat = ft_cnt_repeat(str, dict);
	// dprintf(2, "repeat : %d\n", repeat);
	// exit(0);
	i = 0;
	j = 1;
	len = ft_cntstr(str) - repeat  - 1;
	// dprintf(2, "len : %d\n", len);
	tmp = malloc(sizeof(t_dict_value *) * (len));
	if (!tmp)
		return (NULL);
	int t = 0;
	while (str[j])
	{
		tmp[i] = malloc(sizeof(t_dict_value));
		sp_2 = ft_split(str[j], '=');
		if (sp_2 == NULL)
			return (NULL);
		if (ft_find_repeat(sp_2[0], dict) == EXIT_SUCCESS) // repeat value
		{
			// dprintf(2, "repeat\n");
			ft_instead_value(sp_2, dict);
			t = 1;
		}
		if (t == 0)
		{
			if (sp_2[0])
				tmp[i]->key = ft_strdup(sp_2[0]);
			else
				tmp[i]->key = ft_strdup("");
			if (sp_2[1])
				tmp[i]->value = ft_strdup(sp_2[1]);
			else
				tmp[i]->value = NULL;
			i++;
			t = 0;
		}
		j++;
		// free(sp_2);
		ft_dbfree(sp_2);
	}
	// dprintf(2, "finish_getvalue1\n");
	// tmp[i]->key = NULL;
	// tmp[i]->value = NULL;
	// dprintf(2, "finish_getvalue2\n");
	// exit(0);
	return (tmp);
}

/*av instead value that it want to attach with last arg*/
void	ft_addvalueexport(char **av, t_dict *dict)
{
	t_dict			*tmp_newdict=NULL;
	t_dict_value	**tmp_value;
	int	i;
	int	len;

	i = 0;
	tmp_value =  ft_get_value(av, dict);
	// ft_prtdict_value(tmp_value);
	len = ft_cntdict_export(tmp_value);
	// dprintf(2, "len_add : %d\n", len);
	// exit(0);
	// ft_prtdict(dict);
	while (i < len)
	{
		tmp_newdict = ft_lstnew_dict(tmp_value[i]);
		ft_lstadd_back_dict(&dict, tmp_newdict);
		i++;
	}
	// dprintf(2, "before adddict\n");
	// ft_prtdict(dict);
	// exit(0);
}