/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:04:46 by mgena             #+#    #+#             */
/*   Updated: 2020/03/10 20:56:18 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
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
		ft_printf("usage: env [-i] [-u name]\n"
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

void ft_env_warg(char **command, t_hash_table *table)
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
	ft_printf("usage: env [-i] [-u name]\n"
			  "           [name=value ...]\n");
}

void ft_add_env(char *command)
{
	size_t i;
	char **new_env;

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

void ft_change_env(char **cur_env, char *command)
{
	free(*cur_env);
	*cur_env = ft_strdup(command);
}

char	**ft_setenv(char **command)
{
	char **var;
	char **cur;

	while (*command && ft_strchr(*command, '='))
	{
		var = ft_strsplit(*command, '=');
		if (var[1] == NULL)
		{
			ft_abortalloc(var);
			return command;
		}
		if (!(cur = ft_get_env(*var)))
			ft_add_env(*command);
		else
			ft_change_env(cur, *command);
		ft_abortalloc(var);
		command++;
	}
	return (command);
}

void ft_env_set_temp(char **command, t_hash_table *table)
{
	char **cpy_env;

	cpy_env = g_env;
	g_env = ft_copy_env();
	command = ft_setenv(command);
	if (*command)
	execute_command(command, table);
	else
		ft_print_env();
	ft_abortalloc(g_env);
	g_env = cpy_env;
}

void ft_env(char **command, t_hash_table *table)
{

	if (!command[1])
		ft_print_env();
	else if (command[1][0] == '-')
		ft_env_warg(command, table);
	else
		ft_env_set_temp(&command[1], table);

}

void ft_setenv_cmd(char **command)
{
	command = ft_setenv(&command[1]);
	if (*command)
		ft_printf("usage: setenv [name=value ...]\n");
}

void ft_unsetenv(char **command)
{
	while (*command)
		ft_unset_env(*command++);
	if (*command)
		ft_printf("usage: unsetenv [name ...]\n");
	//TODO make reloading hash table when "PATH" changes
}

void ch_dir_to(char *dir)
{
	char **newpath;

	if (chdir(dir))
	{
		if (!access(dir, 3))
			ft_printf("cd: permission denied: %s\n", dir);
		else
			ft_printf("cd: no such file or directory: %s\n", dir);
		return;
	}
	newpath = ft_memalloc(sizeof(char *) * 2);
	newpath[1] = getcwd(NULL, 1024);
	*newpath = ft_strjoin("PWD=", newpath[1]);
	free(newpath[1]);
	newpath[1] = NULL;
	ft_setenv(newpath);
	ft_abortalloc(newpath);
}

void	msh_cd(char **command)
{
	if (command[1])
	{
		ch_dir_to(command[1]);
	}
	else
	{
		if (*g_env)
			ch_dir_to(ft_get_env_value("HOME"));
		else
			ft_printf("Set HOME environment variable\n");
	}
}

void msh_echo(char **command)
{
	command++;
		while (*command)
		{
			ft_printf("%s ", *command);
			command++;
		}
	ft_printf("\n");
}

void env_commands(char **command, t_hash_table *table)
	{
		if (ft_strcmp(*command, "env") == 0)
			ft_env(command, table);
		else if (ft_strcmp(*command, "unsetenv") == 0)
			ft_unsetenv(command);
		else if (ft_strcmp(*command, "setenv") == 0)
			ft_setenv_cmd(command);
		else if (ft_strcmp(*command, "cd") == 0)
			msh_cd(command);
		else if (ft_strcmp(*command, "echo") == 0)
			msh_echo(command);
	}
