/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 17:51:35 by mgena             #+#    #+#             */
/*   Updated: 2020/03/13 17:51:35 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"

extern char **g_env;
extern int g_sig;

void			del_one_command(void *foo, size_t size __attribute__((unused)))
{
	ft_abortalloc_list(*(char***)foo);
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
	ft_abortalloc_list(tobefree);
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
		if (!g_sig)
			ft_printf("$>");
		g_sig = 0;
		line = msh_readline();
		if (!line)
			break ;
		commands = parse_line(line);
		run_commands(commands, &ht_cmd_path);
		ft_lstdel(&commands, del_one_command);
	}
	del_hash_table(ht_cmd_path);
}
