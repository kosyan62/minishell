/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash..c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 18:59:17 by mgena             #+#    #+#             */
/*   Updated: 2020/03/04 20:13:55 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include <stdio.h>

ht_item *new_ht_item(char *key, char *value)
{
	ht_item *new;

	new = malloc(sizeof(ht_item));
	new->key = key;
	new->value = value;
	return new;
}

ht_hash_table *new_hash_table(unsigned int size)
{
	ht_hash_table *table;
	ht_item **items;
	size_t i;

	i = 0;
	table = malloc(sizeof(ht_hash_table));
	items = malloc(sizeof(ht_item*) * size);
	while (i != size)
		items[i++] = NULL;
	table->items = items;
	table->size = size;
	return (table);
}

void	ht_insert(ht_hash_table *table, char *key, char *value, int i)
{
	table->items[i] = new_ht_item(key, value);
}

int main()
{
	ht_hash_table *table;
	ht_item *cur;
	int i = 0;

	table = new_hash_table(10);
	ht_insert(table, "1", "fuck", 0);
	ht_insert(table, "2", "shit", 2);
	ht_insert(table, "3", "opapa", 2);
	while (i != 10)
	{
		cur = table->items[i++];
		if (cur)
			printf("%s, %s\n", cur->key, cur->value);
		else
			printf("NULL\n");
	}
}