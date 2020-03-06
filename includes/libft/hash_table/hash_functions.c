/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:33:01 by mgena             #+#    #+#             */
/*   Updated: 2020/03/06 15:36:00 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

unsigned int	hash_funct(char *string, int a, int count)
{
	unsigned long	hash;
	int				len;
	int				i;

	hash = 0;
	i = 0;
	len = ft_strlen(string);
	while (i != len)
	{
		hash += ft_pow(a, (len - (i + 1))) * string[i];
		hash %= count;
		i++;
	}
	return ((unsigned int)hash);
}

void			ht_insert(t_hash_table *table, char *key, char *value)
{
	t_ht_item		*item;
	t_ht_item		*cur;
	unsigned int	index;

	item = new_ht_item(key, value);
	index = hash_funct(key, WEIGHT, table->size);
	cur = table->items[index];
	table->items[index] = item;
	table->items[index]->next = cur;
}

char			*ht_search(t_hash_table *table, char *key)
{
	unsigned int	index;
	t_ht_item		*item;

	index = hash_funct(key, WEIGHT, table->size);
	item = table->items[index];
	while (item)
	{
		if (!ft_strcmp(item->key, key))
			return (item->value);
		item = item->next;
	}
	return (NULL);
}

void			ht_print_whole(t_hash_table *table)
{
	int			i;
	t_ht_item	*cur;

	i = 0;
	while (i != 10)
	{
		cur = table->items[i];
		if (cur)
		{
			while (cur)
			{
				ft_printf("%s : %s | %p\n", cur->key, cur->value, cur);
				cur = cur->next;
			}
		}
		else
			ft_printf("items[%i] = NULL\n", i);
		i++;
	}
}