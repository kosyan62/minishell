/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 17:24:18 by mgena             #+#    #+#             */
/*   Updated: 2020/03/13 17:24:18 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"

extern char **g_env;

void		ft_unset_cpy_env(char **command, t_hash_table *table)
{
	char **cpy_env;

	if (!(*command))
	{
		ft_printf("env: option requires an argument -- u\n");
		ft_printf("usage: env [-i] [-u name]\n\t\t\t[name=value ...]\n");
		return ;
	}
	else
	{
		cpy_env = g_env;
		g_env = ft_copy_env();
		ft_unset_tmp(*command, NULL);
		if (!(*(++command)))
		{
			ft_print_env();
		}
		else
			execute_command(command, table);
		ft_abortalloc_list(g_env);
		g_env = cpy_env;
	}
}

void		ft_env_warg(char **command, t_hash_table *table)
{
	if (command[1][1] == 'i')
	{
		ft_ignore_env(&command[2], table);
		return ;
	}
	if (command[1][1] == 'u')
	{
		ft_unset_cpy_env(&command[2], table);
		return ;
	}
	ft_printf("usage: env [-i] [-u name]\n\t\t\t[name=value ...]\n");
}

void		ft_add_env(char *command)
{
	size_t	i;
	char	**new_env;

	i = 0;
	while (g_env[i])
		i++;
	if (!(new_env = ft_memalloc(sizeof(char*) * (i + 2))))
		malloc_error();
	i = 0;
	while (g_env[i])
	{
		new_env[i] = g_env[i];
		i++;
	}
	new_env[i] = ft_strdup(command);
	new_env[i + 1] = NULL;
	free(g_env);
	g_env = new_env;
}

void		ft_change_env(char **cur_env, char *command)
{
	free(*cur_env);
	*cur_env = ft_strdup(command);
}

char		**ft_setenv(char **command, t_hash_table **table)
{
	char **var;
	char **cur;

	while (*command && ft_strchr(*command, '='))
	{
		var = ft_strsplit(*command, '=');
		if (var[1] == NULL)
		{
			ft_abortalloc_list(var);
			return (command);
		}
		if (!(cur = ft_get_env(*var)))
			ft_add_env(*command);
		else
			ft_change_env(cur, *command);
		if (!ft_strcmp(*var, "PATH") && table)
			ft_rewrite_hash_table(table);
		ft_abortalloc_list(var);
		command++;
	}
	return (command);
}
