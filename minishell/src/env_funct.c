/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 17:23:04 by mgena             #+#    #+#             */
/*   Updated: 2020/03/13 17:23:04 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"

extern char **g_env;

void		ft_print_env(void)
{
	char **tmp_env;

	tmp_env = g_env;
	while (*tmp_env)
	{
		ft_printf("%s\n", *tmp_env);
		tmp_env++;
	}
}

size_t		var_count_from_cmd(char **command)
{
	size_t i;

	i = 0;
	while (command[i] && ft_strchr(command[i], '='))
		i++;
	return (i);
}

char		**ft_fill_new_env(char **command)
{
	size_t i;
	size_t k;

	k = 0;
	i = var_count_from_cmd(command);
	if (!(g_env = ft_memalloc(sizeof(*g_env) * (i + 1))))
		malloc_error();
	while (i != k)
	{
		g_env[k] = ft_strdup(command[k]);
		k++;
	}
	g_env[k] = NULL;
	return (&command[k]);
}

void		ft_ignore_env(char **command, t_hash_table *table)
{
	char **tmp_env;

	tmp_env = g_env;
	command = ft_fill_new_env(command);
	if (!*command)
		ft_print_env();
	else
		execute_command(command, table);
	ft_abortalloc(g_env);
	g_env = tmp_env;
}
