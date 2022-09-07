/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cond_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:20:17 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/06 09:13:38 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"

/* Bit-wise AND operation.
 *
 * Encodings
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |    DR     |    SR1    | 0 |   -   |    SR2    |
 * 											 ^ register mode
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |    DR     |    SR1    | 1 |       imm5        |
 * 											 ^ immediate mode
 */
void	and_comparison(uint16_t instr, t_vm *vm)
{
	uint16_t	dr;
	uint16_t	sr1;
	uint16_t	sr2;
	uint16_t	imm_flag;

	dr = instr >> 9 & 0x7;
	sr1 = instr >> 6 & 0x7;
	imm_flag = instr >> 5 & 0x1;
	if (imm_flag)
	{
		vm->regs[dr] = vm->regs[sr1] & sign_extend(instr & 0x1f, 5);
	}
	else
	{
		sr2 = instr & 0x7;
		vm->regs[dr] = vm->regs[sr1] & vm->regs[sr2];
	}
	update_cond(vm, dr);
}

/* Bit-wise complement.
 *
 * Encodings
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |    DR     |    SR     | 1 |     1 1 1 1 1     |
 *
 */
void	complement(uint16_t instr, t_vm *vm)
{
	uint16_t	dr;
	uint16_t	sr;

	dr = instr >> 9 & 0x7;
	sr = instr >> 6 & 0x7;
	vm->regs[dr] = ~(vm->regs[sr]);
	update_cond(vm, dr);
}
