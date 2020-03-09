/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:21:41 by mgena             #+#    #+#             */
/*   Updated: 2020/03/09 21:43:16 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/includes/hash.h>
#include "mshheader.h"
#include <dirent.h>

char **g_env;

void del_one_command(void *foo, size_t bar)
{
	bar = 0;
	free(*(char***)foo);
	free(foo);
}

char **get_cmd_path()
{
	char	*cmd_str;
	char	**cmd_arr;

	cmd_str = ft_get_env_value("PATH");
	cmd_arr = ft_strsplit(cmd_str, ':');
	free(cmd_str);
	return(cmd_arr);
}

void msh_fill_table(t_hash_table *table, char *str)
{
	char *cmd_fullname;
	char	*tmp;
	DIR	*dir;
	struct dirent	*entry;

	if (!(dir = opendir(str)))
	{
		ft_printf("no such command: %s\n", str);
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

t_hash_table *cmd_path_init()
{
	t_hash_table *result;
	char **cmd_paths;
	void *tobefree;

	result = new_hash_table(1500);
	cmd_paths = get_cmd_path();
	tobefree = cmd_paths;
	while (*cmd_paths)
	{
		msh_fill_table(result, *cmd_paths);
		cmd_paths++;
	}
	ft_abortalloc(tobefree);
	return result;
}

void	minishell()
{
	char 	*line;
	t_list	*commands;
	t_hash_table *ht_cmd_path;

	ht_cmd_path = cmd_path_init();
	while (1)
	{
		ft_printf("$>");
		line = msh_readline();
		if (!line)
			break;
		commands = parse_line(line);
		run_commands(commands, ht_cmd_path);
		ft_lstdel(&commands, del_one_command);
		free(line);
	}
	del_hash_table(ht_cmd_path);
}

int 	main()
{
	extern char **environ;

	g_env = environ;
	minishell();

	return 0;
}
