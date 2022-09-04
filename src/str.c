/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:21:18 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/04 22:24:09 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"

/* Store base + offset.
 *
 * Encoding
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |    SR     |    BaseR  |        offset6        |
 *
 */
void	st(uint16_t instr, t_vm *vm)
{
	uint16_t	sr;
	uint16_t	br;
	uint16_t	offset;

	sr = instr >> 9 & 7;
	br = instr >> 6 & 7;
	offset = sign_extend(instr & 0x3f, 6);
	vm->memory[vm->regs[br] + offset] = vm->regs[sr];
}
