/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 17:15:49 by mgena             #+#    #+#             */
/*   Updated: 2020/03/13 17:16:14 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"

extern char **g_env;

void		ch_dir_to(char *dir)
{
	char **newpath;

	if (chdir(dir))
	{
		if (!access(dir, 3))
			ft_printf("cd: permission denied: %s\n", dir);
		else
			ft_printf("cd: no such file or directory: %s\n", dir);
		return ;
	}
	newpath = ft_memalloc(sizeof(char *) * 2);
	newpath[1] = getcwd(NULL, 1024);
	*newpath = ft_strjoin("PWD=", newpath[1]);
	free(newpath[1]);
	newpath[1] = NULL;
	ft_setenv(newpath, NULL);
	ft_abortalloc(newpath);
}

void		msh_cd(char **command)
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

void		ft_remove_quotes(char *str)
{
	size_t i;

	i = 0;
	while (*str)
	{
		if (*str == '"')
		{
			while (str[i])
			{
				str[i] = str[i + 1];
				i++;
			}
		}
		else
			str++;
		i = 0;
	}
}

void		msh_echo(char **command)
{
	command++;
	while (*command)
	{
		ft_remove_quotes(*command);
		ft_printf("%s ", *command);
		command++;
	}
	ft_printf("\n");
}

void		env_commands(char **command, t_hash_table **table)
{
	if (ft_strcmp(*command, "env") == 0)
		ft_env(command, *table);
	else if (ft_strcmp(*command, "unsetenv") == 0)
		ft_unsetenv(command, table);
	else if (ft_strcmp(*command, "setenv") == 0)
		ft_setenv_cmd(command, table);
	else if (ft_strcmp(*command, "cd") == 0)
		msh_cd(command);
	else if (ft_strcmp(*command, "echo") == 0)
		msh_echo(command);
}
