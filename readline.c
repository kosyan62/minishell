/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:19:42 by mgena             #+#    #+#             */
/*   Updated: 2020/02/14 16:50:37 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"
#include <limits.h>
#include <unistd.h>

t_string *write_to_string(t_string line, char *buf)
{
	line.len = 0;
	line.maxlen = BUF_SIZE;
	line.ptr = ft_strnew(line.maxlen);
	while (*buf)
	{
	if (line.len == line.maxlen)
	{
		line.ptr = ft_realloc(line.ptr);
		line.maxlen *= 2;
		line.len += line.maxlen;
	}
	}
}

char	*msh_readline()
{
	t_string	line;
	static char	buf[BUF_SIZE + 1];
	int			red;

	ft_bzero(buf, BUF_SIZE + 1);
	while ((red = read(1, buf, BUF_SIZE)) > 0)
	{
		line = write_to_string(line, buf);
		if(line.len > ARG_MAX)
			break;
	}
	line.ptr[line.len] = '\0';
return (line.ptr);
}

void	parse_line(char *line)
{
	char *original;
	char **command;

	original = line;
	if (*line == ';')
		line++;
	while (*line)
	{
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
