/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:21:41 by mgena             #+#    #+#             */
/*   Updated: 2020/03/07 15:42:16 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/includes/hash.h>
#include "mshheader.h"

void del_one_command(void *foo, size_t bar)
{
	bar = 0;
	free(foo);
}

t_hash_table *cmd_path_init()
{
	t_hash_table *result;

	result = new_hash_table(1500);

	return result;
}

void	minishell()
{
	char 	*line;
	t_list	*commands;
	t_hash_table *ht_cmd_path;

	ht_cmd_path = cmd_path_init();
	while (1)
	{
		ft_printf("$>");
		line = msh_readline();
		if (!line)
			break;
		commands = parse_line(line);
		run_commands(commands);
		ft_lstdel(&commands, del_one_command);
		free(line);
	}
}

int 	main()
{
	minishell();

	return 0;
}
