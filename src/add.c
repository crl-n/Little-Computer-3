/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:27:47 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/04 16:28:15 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"

/* Encodings
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

	dr = instr >> 9 & 0x7;
	sr1 = instr >> 6 & 0x7;
	if (instr >> 5 & 0x1)
	{
		vm->regs[dr] = vm->regs[sr1] + (instr & 0x1f);
		return ;
	}
	sr2 = instr & 0x7;
	vm->regs[dr] = vm->regs[sr1] + vm->regs[sr2];
}
