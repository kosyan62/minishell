/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:21:41 by mgena             #+#    #+#             */
/*   Updated: 2020/03/13 18:01:21 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"
#include <signal.h>

char			**g_env;
int				g_sig;

void	handler(int sig)
{
	if (sig == SIGINT)
		g_sig = 1;
	ft_printf("\n$>");
}

int		main(void)
{
	extern char **environ;

	signal(SIGINT, handler);
	g_env = environ;
	g_env = ft_copy_env();
	g_sig = 0;
	minishell();
	return (0);
}

char	*jump_whitespace(char *line)
{
	while (ft_isspace(*line) && *line)
		line++;
	return (line);
}
