/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:27:47 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/04 20:24:31 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"

/* Addition instruction with two separate modes.
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
void	add(uint16_t instr, t_vm *vm)
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
		vm->regs[dr] = vm->regs[sr1] + sign_extend(instr & 0x1f, 5);
		return ;
	}
	sr2 = instr & 0x7;
	vm->regs[dr] = vm->regs[sr1] + vm->regs[sr2];
	update_cond(vm, dr);
}
