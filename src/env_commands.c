/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:04:46 by mgena             #+#    #+#             */
/*   Updated: 2020/03/09 23:45:47 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"

extern char **g_env;

void	ft_print_env()
{
	char **tmp_env;

	tmp_env = g_env;

	while(*tmp_env)
	{
		ft_printf("%s\n", *tmp_env);
		tmp_env++;
	}
}

size_t var_count_from_cmd(char **command)
{
	size_t i;

	i = 0;
	while (command[i] && ft_strchr(command[i], '='))
		i++;
	return (i);
}
char **ft_fill_new_env(char **command)
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

void	ft_ignore_env(char **command, t_hash_table *table)
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

char **ft_copy_env()
{
	size_t i;
	char **cpy_env;

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
	return cpy_env;
}

void ft_unset_env(char *name)
{
	char	**src;
	size_t i;

	i = 0;
	if (!(src = ft_get_env(name)))
		return;
	free(src[i]);
	while (src[i])
	{
		src[i] = src[i + 1];
		i++;
	}
	src[i] = NULL;
}

void ft_unset_cpy_env(char **command, t_hash_table *table)
{
	char **cpy_env;

	if (!(*command))
	{
		ft_printf("env: option requires an argument -- u\n");
		ft_printf("usage: env [-iv] [-u name]\n"
				  "           [name=value ...]\n");
		return ;
	}
	else
	{
		cpy_env = g_env;
		g_env = ft_copy_env();
		ft_unset_env(*command);
		if (!(*(++command)))
		{
			ft_print_env();
		}
		else
			execute_command(command, table);
		ft_abortalloc(g_env);
		g_env = cpy_env;
	}
}

void ft_env(char **command, t_hash_table *table)
{

	if (!command[1])
	{
		ft_print_env();
		return ;
	}
	if (command[1][0] == '-')
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
		ft_printf("usage: env [-iv] [-u name]\n"
				  "           [name=value ...]\n");
		return ;
	}

}

//void ft_setenv(char **command)
//{
//	if (*command[1])
//	{
//		ft_printf("setenv usage :<variable> <equal>\n");
//		return ;
//	}
//	ft_search_env(*command);
//}
//void ft_unsetenv(char **command);
//void ft_cd(char **command);
//
//
void env_commands(char **command, t_hash_table *ht_cmd_path)
{
//	void (*my_choise)(char**);
	if (ft_strcmp(*command, "env") == 0)
		ft_env(command, ht_cmd_path);
//	else if (ft_strcmp(*command, "unsetenv") == 0)
//		my_choise = ft_unsetenv;
//	else if (ft_strcmp(*command, "setenv") == 0)
//		my_choise = ft_setenv;
//	else if (ft_strcmp(*command, "cd") == 0)
//		my_choise = ft_cd;
//	my_choise(command);
}