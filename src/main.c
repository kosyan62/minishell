/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:21:41 by mgena             #+#    #+#             */
/*   Updated: 2020/03/04 15:02:51 by mgena            ###   ########.fr       */
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
		if (line && (var = ft_strcmp(line, "exit")) == 0)
			break;
		parse_line(line);
	}
}

int 	main()
{
	minishell();

	return 0;
}
