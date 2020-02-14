/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:21:41 by mgena             #+#    #+#             */
/*   Updated: 2020/02/13 17:50:04 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"

void	minishell()
{
	char *line;
	int var;

	while (1)
	{
		ft_printf("$>");
		line = msh_readline();
		if ((var = ft_strcmp(line, "exit")) == 0)
		{
			free(line);
			break;
		}
		parse_line(line);
	}
}

int 	main()
{
	minishell();
	return 0;
}