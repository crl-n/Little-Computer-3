/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:26:28 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/04 20:54:45 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"

/* Conditional branch instruction.
 *
 * Encoding
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     | n | z | p |             PCoffset9             |
 *
 */
void	branch(uint16_t instr, t_vm *vm)
{
	uint16_t	offset;
	uint16_t	nzp;

	nzp = instr >> 9 & 0x7;
	if (nzp & vm->regs[R_COND])
	{
		offset = sign_extend(instr & 0xff1, 9);
		vm->regs[R_PC] += offset;
	}
	update_cond(vm, R_PC);
}
