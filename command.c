/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:11:37 by mgena             #+#    #+#             */
/*   Updated: 2020/02/14 15:12:44 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"
#include <sys/wait.h>

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
char	**pars_commands(char *line)
{
	int		quantity;
	int		k;
	char	**argv;


	k = 0;
	quantity = get_quantity(line);
	argv = malloc((sizeof(char*)) * (quantity + 1));
	while (*line != '\0')
	{
		argv[k++] = line;
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
		**line = '\0';
	else
		*line = &tmp[ft_strlen(tmp)];
	(*line)++;
	return (pars_commands(tmp));
}

void	execute_command(char **command)
{
	pid_t	pid;
	int		status;
	char	*filename;

	filename = "/bin/";
	filename = ft_strjoin(filename, *command);
	pid = fork();
	if (pid == 0)
	{
		if (execv(filename, command) == -1)
			error("Execute error");
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
