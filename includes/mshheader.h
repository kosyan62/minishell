/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshheader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:22:22 by mgena             #+#    #+#             */
/*   Updated: 2020/03/06 22:01:33 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MSHHEADER_H
#define MINISHELL_MSHHEADER_H
#define BUF_SIZE 8

# include "libft.h"
# include <unistd.h>

typedef	struct		s_string
{
	char			*ptr;
	size_t			len;
	size_t			maxlen;
}					t_string;

char 	*msh_readline();
t_list 	*parse_line(char *line);
void	error(char *line);
char ** get_command(char **line);
void	execute_command(char **command);
void	env_commands(char **command);
void	run_commands(t_list *command);

#endif //MINISHELL_MSHHEADER_H
