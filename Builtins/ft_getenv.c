/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:50:33 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/10 16:13:30 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_dict_value	**ft_getvalue_env(char **env)
{
	int				line_env;
	t_dict_value	**tmp_dict;
	char			**tmp_env;
	int				i;

	line_env = ft_cntstr(env);
	i = 0;
	tmp_dict = malloc(sizeof(t_dict_value *) * (line_env + 1));
	if (!tmp_dict)
		return (NULL);
	while (i < line_env)
	{
		tmp_dict[i] = malloc(sizeof(t_dict_value));
		tmp_env = ft_split(env[i], '=');
		if (tmp_env[0])
			tmp_dict[i]->key = ft_strdup(tmp_env[0]);
		else
			tmp_dict[i]->key = ft_strdup("");
		if (tmp_env[1])
			tmp_dict[i]->value = ft_strdup(tmp_env[1]);
		else
			tmp_dict[i]->value = NULL;
		i++;
	}
	return (tmp_dict);
}

// t_dict *ft_env_forexport(char **env)
t_dict	*ft_getenv(char **env)
{
	int				i;
	int				len;
	t_dict_value	**tmp_env;
	t_dict			*tmp;
	t_dict			*dict;

	dict = NULL;
	i = 0;
	tmp_env = ft_getvalue_env(env);
	len = ft_cntstr(env);
	while (i < len)
	{
		if (dict == NULL)
			dict = ft_lstnew_dict(tmp_env[i]);
		else
		{
			tmp = ft_lstnew_dict(tmp_env[i]);
			ft_lstadd_back_dict(&dict, tmp);
		}
		i++;
	}
	return (dict);
}
