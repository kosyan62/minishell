/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:19:42 by mgena             #+#    #+#             */
/*   Updated: 2020/02/25 19:38:24 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"
#include <limits.h>
#include <unistd.h>


char *ft_get_env(char *name)
{
	extern char **environ;
	char *res;

	while (*environ != NULL)
	{
		if (ft_strstr(*environ, name))
		{
			res = ft_strchr(*environ, '=');
			return ft_strdup(res + 1);
		}
		environ++;
	}
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

//char *get_dollar(char *line, size_t  i)
//{
//
//}

char *get_expansion(char *line)
{
	size_t i;

	i = 0;
	while (line[i] != 0)
	{
		if (line[i] == '~')
			get_tilda(&line, i);
//		else if (line[i] == '$')
//			line = get_dollar(line, i);
		i++;
	}
//	ft_printf("!!!!%s\n", line);
	return line;
}

char	*msh_readline()
{
	char	*line;

	line = NULL;
	if (get_next_line(0, &line) == 0)
		return NULL;
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
