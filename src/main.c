/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:21:41 by mgena             #+#    #+#             */
/*   Updated: 2020/03/10 19:00:49 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"
#include <dirent.h>

char			**g_env;
int				signa;

void			del_one_command(void *foo, size_t bar)
{
	bar = 0;
	ft_abortalloc(*(char***)foo);
	free(foo);
}

char			**get_cmd_path(void)
{
	char	*cmd_str;
	char	**cmd_arr;

	if (*g_env)
	{
		if (!(cmd_str = ft_get_env_value("PATH")))
			return (NULL);
	}
	else
		cmd_str = ft_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	cmd_arr = ft_strsplit(cmd_str, ':');
	free(cmd_str);
	return (cmd_arr);
}

void			msh_fill_table(t_hash_table *table, char *str)
{
	char			*cmd_fullname;
	char			*tmp;
	DIR				*dir;
	struct dirent	*entry;

	if (!(dir = opendir(str)))
	{
		return ;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		tmp = ft_strjoin(str, "/");
		cmd_fullname = ft_strjoin(tmp, entry->d_name);
		ht_insert(table, entry->d_name, cmd_fullname);
		free(cmd_fullname);
		free(tmp);
	}
	closedir(dir);
}

t_hash_table	*cmd_path_init(void)
{
	t_hash_table	*result;
	char			**cmd_paths;
	void			*tobefree;

	result = new_hash_table(1500);
	if (!(cmd_paths = get_cmd_path()))
	{
		del_hash_table(result);
		return (new_hash_table(0));
	}
	tobefree = cmd_paths;
	while (*cmd_paths)
	{
		msh_fill_table(result, *cmd_paths);
		cmd_paths++;
	}
	ft_abortalloc(tobefree);
	return (result);
}

void			minishell(void)
{
	char			*line;
	t_list			*commands;
	t_hash_table	*ht_cmd_path;

	ht_cmd_path = cmd_path_init();
	while (1)
	{
		ft_printf("$>");
		line = msh_readline();
		if (!line)
			break ;
		commands = parse_line(line);
		run_commands(commands, &ht_cmd_path);
		ft_lstdel(&commands, del_one_command);
	}
	del_hash_table(ht_cmd_path);
}

void handler()
{
	ft_printf("\n");
	minishell();
}
int				main(void)
{
	extern char **environ;

	signal(SIGINT, handler);
	g_env = environ;
	g_env = ft_copy_env();
	minishell();
	return (0);
}
