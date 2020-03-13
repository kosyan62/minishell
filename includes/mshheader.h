/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshheader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:22:22 by mgena             #+#    #+#             */
/*   Updated: 2020/03/13 18:03:33 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MSHHEADER_H
# define MINISHELL_MSHHEADER_H
# define BUF_SIZE 8

# include "libft.h"
# include <unistd.h>
# include <dirent.h>

void				minishell(void);
char				*msh_readline();
char				*get_expansion(char *line);
void				ft_env(char **command, t_hash_table *table);
char				**ft_setenv(char **command, t_hash_table **table);
void				ft_setenv_cmd(char **command, t_hash_table **table);
void				ft_unsetenv(char **command, t_hash_table **table);
void				ft_unset_tmp(char *name, t_hash_table **table);
void				ft_print_env(void);
void				ft_ignore_env(char **command, t_hash_table *table);
void				ft_env_warg(char **command, t_hash_table *table);
void				ft_rewrite_hash_table(t_hash_table **table);
t_list				*parse_line(char *line);
void				error(char *line);
char				**get_command(char **line);
void				execute_command(char **command, t_hash_table *table);
void				env_commands(char **command, t_hash_table **ht_cmd_path);
void				run_commands(t_list *command, t_hash_table **ptr);
char				*ft_get_env_value(char *name);
char				**ft_get_env(char *name);
char				**ft_copy_env();
char				*get_expansion(char *line);
char				*jump_quotes(char *line);
t_hash_table		*cmd_path_init(void);
char				*jump_whitespace(char *line);

#endif
