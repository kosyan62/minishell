/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:19:42 by mgena             #+#    #+#             */
/*   Updated: 2020/03/13 17:47:12 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"
#include <limits.h>
#include <unistd.h>

extern char	**g_env;
extern int	g_sig;

char		**ft_get_env(char *name)
{
	size_t len;
	size_t i;

	i = 0;
	len = ft_strlen(name);
	while (g_env[i] && name)
	{
		if (ft_strnstr(g_env[i], name, len))
		{
			if (g_env[i][len] == '=')
				return (&g_env[i]);
		}
		i++;
	}
	return (NULL);
}

char		*ft_get_env_value(char *name)
{
	char	*res;
	char	**place;

	if (!(place = ft_get_env(name)))
		return (NULL);
	else
	{
		res = *place;
		res = ft_strchr(res, '=');
		if (!(res = ft_strdup(res + 1)))
			malloc_error();
		return (res);
	}
}

char		*msh_readline(void)
{
	char	*line;

	line = NULL;
	if ((get_next_line(0, &line) == 0) || !line)
		return (ft_strnew(1));
	if (ft_strcmp(line, "exit") == 0)
	{
		get_next_line(-1, &line);
		return (NULL);
	}
	if (g_sig)
		g_sig = 0;
	return (line);
}

t_list		*parse_line(char *line)
{
	char	*original;
	char	**one_command;
	t_list	*commands;

	commands = NULL;
	original = line;
	if (*line == ';')
		line++;
	while (1)
	{
		if (*line == '\0')
			break ;
		if (*line == ';')
		{
			ft_printf("parse error near `;;'\n");
			free(original);
			return (NULL);
		}
		one_command = get_command(&line);
		ft_lstaddend(&commands, ft_lstnew(&one_command, sizeof(&one_command)));
	}
	free(original);
	return (commands);
}

void		run_commands(t_list *command, t_hash_table **ht_cmd_path)
{
	if (!command)
		return ;
	while (command && **(char***)command->content)
	{
		if (ft_strcmp(**(char ***)(command->content), "cd") == 0 ||
			ft_strcmp(**(char ***)command->content, "setenv") == 0 ||
			ft_strcmp(**(char ***)command->content, "unsetenv") == 0 ||
			ft_strcmp(**(char ***)command->content, "env") == 0 ||
			ft_strcmp(**(char ***)command->content, "echo") == 0)
			env_commands(*(char ***)command->content, ht_cmd_path);
		else
			execute_command(*(char ***)command->content, *ht_cmd_path);
		command = command->next;
	}
}
