/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jsr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:29:05 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/04 21:37:05 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"

/* Jumpt to subroutine.
 *
 * Encodings
 *
 * JSR:
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     | 1 |               PCoffset11                  |
 *
 * JSRR:
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     | 0 |   --  |   BaseR   |          --           |
 *
 */
void	jump(uint16_t instr, t_vm *vm)
{
	uint16_t	br;
	uint16_t	offset;

	if (instr >> 11 & 1)
	{
		offset = instr & 0x7ff;
		vm->regs[R_PC] = sign_extend(offset, 11);
		return ;
	}
	br = instr >> 6 & 7;
	vm->regs[R_PC] = vm->regs[br];
}
