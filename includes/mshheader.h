/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshheader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:22:22 by mgena             #+#    #+#             */
/*   Updated: 2020/03/07 21:23:50 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MSHHEADER_H
#define MINISHELL_MSHHEADER_H
#define BUF_SIZE 8

# include "libft.h"
# include <unistd.h>
#include <libft/includes/hash.h>

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
void execute_command(char **command, t_hash_table *table);
void env_commands(char **command, t_hash_table *ht_cmd_path);
void	run_commands(t_list *command, t_hash_table *ptr);
char	*ft_get_env(char *name);

#endif //MINISHELL_MSHHEADER_H
