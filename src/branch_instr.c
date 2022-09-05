/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:26:28 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/05 12:55:39 by cnysten          ###   ########.fr       */
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
void	br(uint16_t instr, t_vm *vm)
{
	uint16_t	offset;
	uint16_t	nzp;

	nzp = instr >> 9 & 0x7;
	if (nzp & vm->regs[R_COND])
	{
		offset = sign_extend(instr & 0xff1, 9);
		vm->regs[R_PC] += offset;
	}
	//update_cond(vm, R_PC); //Why no update?
}

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
void	jsr(uint16_t instr, t_vm *vm)
{
	uint16_t	br;
	uint16_t	offset;

	vm->regs[R_R7] = vm->regs[R_PC];
	if (instr >> 11 & 1)
	{
		offset = instr & 0x7ff;
		vm->regs[R_PC] = sign_extend(offset, 11);
		return ;
	}
	br = instr >> 6 & 7;
	vm->regs[R_PC] = vm->regs[br];
}

/* Conditional jump instruction.
 *
 * Encodings
 *
 * Jump:
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |    --     |   BaseR   |          --           |
 *
 * Return:
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |    --     |    111    |          --           |
 *
 */
void	jmp(uint16_t instr, t_vm *vm)
{
	uint16_t	br;

	br = instr >> 6 & 7;
	vm->regs[R_PC] = vm->regs[br];
}
