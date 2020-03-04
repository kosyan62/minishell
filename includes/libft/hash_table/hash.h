/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 18:38:30 by mgena             #+#    #+#             */
/*   Updated: 2020/03/04 19:00:55 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct lst_ht_item
{
	char			*key;
	char			*value;
	struct lst_ht_item	*next;
} ht_item;

typedef struct
{
	unsigned int	size;
	ht_item			**items;
} ht_hash_table;