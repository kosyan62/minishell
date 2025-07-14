/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 17:25:21 by mgena             #+#    #+#             */
/*   Updated: 2020/03/13 17:25:21 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"

extern char **g_env;

void		ft_env_set_temp(char **command, t_hash_table *table)
{
	char **cpy_env;

	cpy_env = g_env;
	g_env = ft_copy_env();
	command = ft_setenv(command, NULL);
	if (*command)
		execute_command(command, table);
	else
		ft_print_env();
	ft_abortalloc_list(g_env);
	g_env = cpy_env;
}

void		ft_env(char **command, t_hash_table *table)
{
	if (!command[1])
		ft_print_env();
	else if (command[1][0] == '-')
		ft_env_warg(command, table);
	else
		ft_env_set_temp(&command[1], table);
}
