/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:29:17 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/04 16:29:26 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"

/* Encoding
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |       -       |           TRAPCODE            |
 *
 */
void	trap(uint16_t instr, t_vm *vm)
{
	uint16_t	trapcode;

	trapcode = instr & 0xff;
	if (trapcode == 0x25)
		vm->running = 0;
}
