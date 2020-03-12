/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:19:42 by mgena             #+#    #+#             */
/*   Updated: 2020/03/10 19:06:40 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"
#include <limits.h>
#include <unistd.h>

extern char	**g_env;

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

void		get_tilda(char **line, size_t i)
{
	char *tmp;
	char *tmp2;
	char *str[3];

	tmp = *line;
	tmp[i] = '\0';
	if (!(str[0] = ft_strdup(tmp)))
		malloc_error();
	str[1] = ft_get_env_value("HOME");
	if (!(str[2] = ft_strdup(&tmp[i + 1])))
		malloc_error();
	free(*line);
	if (!(tmp = ft_strjoin(str[0], str[1])))
		malloc_error();
	free(str[0]);
	free(str[1]);
	if (!(tmp2 = ft_strjoin(tmp, str[2])))
		malloc_error();
	free(tmp);
	free(str[2]);
	*line = tmp2;
}

size_t		get_dollr_var(char *src, char **dst)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!ft_isalpha(src[i]) && src[i] != '_')
	{
		*dst = ft_strnew(1);
		return (2);
	}
	while (src[i] && (ft_isalnum(src[i]) || src[i] == '_'))
		i++;
	tmp = ft_strnew(i);
	ft_strncpy(tmp, src, i);
	*dst = ft_get_env_value(tmp);
	free(tmp);
	if (*dst == NULL)
		*dst = ft_strnew(1);
	return (i + 1);
}

void		get_dollar(char **line, size_t i)
{
	char	*tmp;
	char	*tmp2;
	char	*str[3];
	size_t	sp;

	tmp = *line;
	tmp[i] = '\0';
	str[0] = ft_strdup(tmp);
	sp = get_dollr_var(&tmp[i + 1], &str[1]);
	str[2] = ft_strdup(&tmp[i + sp]);
	free(*line);
	tmp = ft_strjoin(str[0], str[1]);
	free(str[0]);
	free(str[1]);
	tmp2 = ft_strjoin(tmp, str[2]);
	free(tmp);
	free(str[2]);
	*line = tmp2;
}

char		*get_expansion(char *line)
{
	size_t i;

	if (!g_env)
		return (line);
	i = 0;
	while (line[i] != 0)
	{
		if (line[i] == '~')
			get_tilda(&line, i);
		else if (line[i] == '$')
			get_dollar(&line, i);
		i++;
	}
	return (line);
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
			free(line);
			free(original);
			error("parse error near `;;'");
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
	while (command)
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
