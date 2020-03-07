/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:04:46 by mgena             #+#    #+#             */
/*   Updated: 2020/03/06 23:00:19 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshheader.h"

extern char **g_env;

//void ft_env(char **command);
//
//void ft_setenv(char ** command);
//void ft_unsetenv(char **command);
//void ft_cd(char **command);


void env_commands(char **command)
{
	void (*my_choise)(char**);

	my_choise = NULL;
//	if (ft_strcmp(*command, "env") == 0)
//		my_choise = ft_env;
//	else if (ft_strcmp(*command, "unsetenv") == 0)
//		my_choise = ft_unsetenv;
//	else if (ft_strcmp(*command, "setenv") == 0)
//		my_choise = ft_setenv;
//	else if (ft_strcmp(*command, "cd") == 0)
//		my_choise = ft_cd;
	my_choise(command);
}