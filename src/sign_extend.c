/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_extend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:23:33 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/06 00:09:32 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint16_t	sign_extend(uint16_t val, int bit_count)
{
	if ((val >> (bit_count - 1)) & 1)
		return ((0xffff << bit_count) | val);
	return (val);
}
