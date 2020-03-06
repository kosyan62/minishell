/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isspace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:02:03 by mgena             #+#    #+#             */
/*   Updated: 2020/03/06 16:01:29 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

_Bool	ft_isspace(int ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' ||
	ch == '\f' || ch == '\r')
		return (1);
	else
		return (0);
}
