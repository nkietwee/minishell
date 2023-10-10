/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:33:01 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/11 00:39:38 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_atol_exit(char *str)
{
	size_t	i;
	size_t	sign;
	size_t	n;

	n = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		n = (n * 10) + (str[i++] - '0');
		if (((n >= 9223372036854775807) && (sign < 0)) \
		|| ((n > 9223372036854775807) && (sign < 0)))
			return (-1);
	}
	return (n * sign);
}

int	ft_checknbr_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	ft_print_exit(size_t nbr, int len, char **cmd, t_minishell *ms)
{
	if (len > 1)
	{
		ft_putstr_fd("exit\n", 2);
		if (nbr >= 9223372036854775807 \
		|| ft_checknbr_exit(cmd[1]) == EXIT_FAILURE)
		{
			ft_putstr_fd("bash: exit : ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			clear_minishell(ms);
			exit(255);
		}
		else if (ft_checknbr_exit(cmd[1]) == EXIT_SUCCESS && len > 2)
		{
			ft_putstr_fd("bash: exit:too many arguments\n", \
			STDOUT_FILENO);
		}
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
}

void	free_dict(t_dict *dict)
{
	t_dict	*to_free;

	while (dict)
	{
		if (dict->tmp_dict->key != NULL)
			free(dict->tmp_dict->key);
		if (dict->tmp_dict->value != NULL)
			free(dict->tmp_dict->value);
		free(dict->tmp_dict);
		to_free = dict;
		dict = dict->next;
		free(to_free);
	}
}

void	ft_exit(char **cmd, t_minishell *ms)
{
	int		i;
	int		len;
	size_t	nbr;

	i = 0;
	len = ft_cntstr(cmd);
	if (cmd[1])
		nbr = ft_atol_exit(cmd[1]);
	if (len == 1 || (len == 2 && nbr < 9223372036854775807 \
	&& ft_checknbr_exit(cmd[1]) == EXIT_SUCCESS))
	{
		ft_putstr_fd("exit\n", 2);
		// free_dict(dict);
		clear_minishell(ms);
		exit(nbr % 256);
	}
	ft_print_exit(nbr, len, cmd, ms);
}
