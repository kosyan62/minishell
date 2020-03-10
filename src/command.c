/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:11:37 by mgena             #+#    #+#             */
/*   Updated: 2020/03/09 16:16:08 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

extern char **g_env;

char	*jump_whitespace(char *line)
{
	while (ft_isspace(*line) && *line)
		line++;
	return (line);
}

int		get_quantity(char *line)
{
	size_t	i;
	int		flag;
	int 	quantity;

	i = 0;
	flag = 0;
	quantity = 0;
	while (line[i] != '\0')
	{
		if (!ft_isspace(line[i]) && flag == 0)
		{
			flag = 1;
			quantity++;
		}
		else if (ft_isspace(line[i]))
			flag = 0;
		i++;
	}
	return (quantity);
}

char *jump_quotes(char *line)
{
	while(*line && *line != 34)
		line++;
	return(++line);
}

char	**pars_commands(char *line)
{
	int		quantity;
	int		k;
	char	**argv;

	k = 0;
	quantity = get_quantity(line);
	if (!(argv = (char**)ft_memalloc((sizeof(char*)) * (quantity + 1))))
		malloc_error();
	while (*line != '\0')
	{
		argv[k++] = line;
		if (*line == 34)
			line = jump_quotes(line);
		while(!ft_isspace(*line) && *line)
			line++;
		if (*line)
		{
			*line = '\0';
			line++;
		}
		line = jump_whitespace(line);
	}
	argv[k] = NULL;
	return(argv);
}

char **get_command(char **line)
{
	char *tmp;

	*line = jump_whitespace(*line);
	tmp = *line;
	*line = ft_strchr(*line, (int) ';');
	if (*line != NULL)
	{
		**line = '\0';
		(*line)++;
	}
	else
		*line = &tmp[ft_strlen(tmp)];
	return (pars_commands(tmp));
}

void execute_command(char **command, t_hash_table *table)
{
	pid_t	pid;
	int		status;
	char	*filename;

	if (!(filename = ht_search(table, *command)))
		filename = *command;
	pid = fork();
	if (pid == 0)
	{
		if (execve(filename, command, g_env) == -1)
		{
			ft_printf("no such command: %s\n", *command);
			return ;
		}
	}
	else if (pid < 0)
		error("Fork error");
	else
	{
			pid = wait(&status);
			if (pid == -1)
				error("Problem with Wait");
			if (status)
				error("Something with child process");
	}
}
