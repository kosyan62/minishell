/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:19:42 by mgena             #+#    #+#             */
/*   Updated: 2020/03/04 17:42:26 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"
#include <limits.h>
#include <unistd.h>


char *ft_get_env(char *name)
{
	char *res;
	size_t len;
	char **dst;

	len = ft_strlen(name);
	dst = environ;
	while (*environ != NULL && *name)
	{
		if (ft_strnstr(*environ, name, len))
		{
			res = ft_strchr(*environ, '=');
			environ = dst;
			return ft_strdup(res + 1);
		}
		environ++;
	}
	environ = dst;
	return NULL;
}

void	get_tilda(char **line, size_t i)
{
	char *tmp;
	char *tmp2;
	char *str[3];

	tmp = *line;
	tmp[i] = '\0';
	str[0] = ft_strdup(tmp);
	str[1] = ft_get_env("HOME");
	str[2] = ft_strdup(&tmp[i + 1]);
	free(*line);
	tmp = ft_strjoin(str[0], str[1]);
	free(str[0]);
	free(str[1]);
	tmp2 = ft_strjoin(tmp, str[2]);
	free(tmp);
	free(str[2]);
	*line = tmp2;
}

size_t get_dollr_var(char *src, char **dst)
{
	size_t i;
	char *tmp;

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
	*dst = ft_get_env(tmp);
	free(tmp);
	if (*dst == NULL)
		*dst = ft_strnew(1);
	return i + 1;
}

void	get_dollar(char **line, size_t  i)
{
	char *tmp;
	char *tmp2;
	char *str[3];
	size_t sp;

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

char *get_expansion(char *line)
{
	size_t i;

	i = 0;
	while (line[i] != 0)
	{
		if (line[i] == '~')
			get_tilda(&line, i);
		else if (line[i] == '$')
			get_dollar(&line, i);
		i++;
	}
	return line;
}

char	*msh_readline()
{
	char	*line;

	line = NULL;
	if (get_next_line(0, &line) == 0)
		return NULL;
	if (ft_strcmp(line, "exit") == 0)
	{
		get_next_line(-1, &line);
//		free(line);
		exit(EXIT_SUCCESS);
	}
	line = get_expansion(line);
return (line);
}

void	parse_line(char *line)
{
	char *original;
	char **command;

	original = line;
	if (*line == ';')
		line++;
	while (1)
	{
		if (*line == '\0')
			break ;
		if (*line == ';')
		{
			free(original);
			error("parse error near `;;'");
		}
		command = get_command(&line);
		if (ft_strcmp(*command, "cd") == 0 || ft_strcmp(*command, "setenv") == 0 ||
		ft_strcmp(*command, "unsetenv") == 0 || ft_strcmp(*command, "env") == 0)
			env_commands(command);
		else
			execute_command(command);
		free(command);
	}
	free(original);
}
