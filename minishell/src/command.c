/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:11:37 by mgena             #+#    #+#             */
/*   Updated: 2020/03/13 17:59:31 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

extern char **g_env;

char		*jump_quotes(char *line)
{
	line++;
	while (*line && *line != '"')
		line++;
	return (++line);
}

size_t		get_quantity(char **line)
{
	int		flag;
	size_t	quantity;

	flag = 0;
	quantity = 0;
	while (**line != '\0' && **line != ';')
	{
		if (!ft_isspace(**line))
		{
			if (flag == 0)
			{
				if (**line == '"')
					*line = jump_quotes(*line);
				flag = 1;
				quantity++;
			}
		}
		else
			flag = 0;
		(*line)++;
	}
	if (**line)
		*((*line)++) = '\0';
	return (quantity);
}

char		**pars_commands(char *line, char **argv)
{
	int		k;
	char	*cmd;

	k = 0;
	cmd = line;
	while (*line != '\0')
	{
		if (*line == '"')
			line = jump_quotes(line);
		while (*line && !ft_isspace(*line))
			line++;
		if (*line)
		{
			*line = '\0';
			line++;
		}
		argv[k++] = ft_strdup(cmd);
		argv[k - 1] = get_expansion(argv[k - 1]);
		line = jump_whitespace(line);
		cmd = line;
	}
	argv[k] = NULL;
	return (argv);
}

char		**get_command(char **line)
{
	char	*tmp;
	char	**argv;
	size_t	quantity;

	*line = jump_whitespace(*line);
	tmp = *line;
	quantity = get_quantity(line);
	if (!(argv = (char**)ft_memalloc((sizeof(char*)) * (quantity + 1))))
		malloc_error();
	pars_commands(tmp, argv);
	return (argv);
}

void		execute_command(char **command, t_hash_table *table)
{
	pid_t	pid;
	char	*filename;

	if (!(filename = ht_search(table, *command)))
		filename = *command;
	pid = fork();
	if (pid == 0)
	{
		if (execve(filename, command, g_env) == -1)
		{
			ft_printf("no such command: %s\n", *command);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		error("Fork error");
	else
	{
		wait(0);
		if (pid == -1)
			error("Problem with Wait");
	}
}
