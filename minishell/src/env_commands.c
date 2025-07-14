/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:04:46 by mgena             #+#    #+#             */
/*   Updated: 2020/03/13 18:04:14 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "mshheader.h"

extern char **g_env;

void		ft_rewrite_hash_table(t_hash_table **table)
{
	del_hash_table(*table);
	*table = cmd_path_init();
}

char		**ft_copy_env(void)
{
	size_t	i;
	char	**cpy_env;

	i = 0;
	while (g_env[i])
		i++;
	if (!(cpy_env = ft_memalloc(sizeof(*g_env) * (i + 1))))
		malloc_error();
	i = 0;
	while (g_env[i])
	{
		cpy_env[i] = ft_strdup(g_env[i]);
		i++;
	}
	cpy_env[i] = NULL;
	return (cpy_env);
}

void		ft_unset_tmp(char *name, t_hash_table **table)
{
	char	**src;
	size_t	i;

	i = 0;
	if (!(src = ft_get_env(name)))
		return ;
	free(src[i]);
	while (src[i])
	{
		src[i] = src[i + 1];
		i++;
	}
	src[i] = NULL;
	if (!ft_strcmp(name, "PATH") && table)
		ft_rewrite_hash_table(table);
}

void		ft_setenv_cmd(char **command, t_hash_table **table)
{
	command = ft_setenv(&command[1], table);
	if (*command)
		ft_printf("usage: setenv [name=value ...]\n");
}

void		ft_unsetenv(char **command, t_hash_table **table)
{
	while (*command)
		ft_unset_tmp(*command++, table);
	if (*command)
		ft_printf("usage: unsetenv [name ...]\n");
}
