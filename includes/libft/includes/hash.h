/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 18:38:30 by mgena             #+#    #+#             */
/*   Updated: 2020/03/06 15:31:28 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "libft.h"
# define WEIGHT 12

typedef struct			s_ht_item
{
	char				*key;
	char				*value;
	struct s_ht_item	*next;
}						t_ht_item;

typedef	struct
{
	unsigned int		size;
	t_ht_item			**items;
}						t_hash_table;

t_ht_item				*new_ht_item(char *key, char *value);
t_hash_table			*new_hash_table(unsigned int size);
void					ht_del_item(t_ht_item *item);
void					del_hash_table(t_hash_table *table);
unsigned int			hash_funct(char *string, int a, int count);
void					ht_insert(t_hash_table *table, char *key, char *value);
char					*ht_search(t_hash_table *table, char *key);
void					ht_del_elem(t_hash_table *table, char *key);
void					ht_print_whole(t_hash_table *table);

#endif
