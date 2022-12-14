/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:13:56 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/06 09:17:14 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"

/* Store. Stores the contents of SR at PC + PCoffset.
 *
 * Encoding
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |    SR     |             PCoffset9             |
 *
 */
void	st(uint16_t instr, t_vm *vm)
{
	uint16_t	sr;
	uint16_t	offset;

	sr = (instr >> 9) & 0x7;
	offset = sign_extend(instr & 0x1ff, 9);
	mem_write(vm, vm->regs[R_PC] + offset, vm->regs[sr]);
}

/* Store indirect. Stores the contents of SR at the address pointed to
 * by PC + PCoffset.
 *
 * Encoding
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |    SR     |             PCoffset9             |
 *
 */
void	sti(uint16_t instr, t_vm *vm)
{
	uint16_t	sr;
	uint16_t	offset;

	sr = (instr >> 9) & 0x7;
	offset = sign_extend(instr & 0x1ff, 9);
	mem_write(vm, mem_read(vm, vm->regs[R_PC] + offset), vm->regs[sr]);
}

/* Store base + offset.
 *
 * Encoding
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |    SR     |    BaseR  |        offset6        |
 *
 */
void	str(uint16_t instr, t_vm *vm)
{
	uint16_t	sr;
	uint16_t	br;
	uint16_t	offset;

	sr = (instr >> 9) & 0x7;
	br = (instr >> 6) & 0x7;
	offset = sign_extend(instr & 0x3f, 6);
	mem_write(vm, vm->regs[br] + offset, vm->regs[sr]);
}
