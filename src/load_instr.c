/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_instr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:40:51 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/05 12:41:01 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"

/* Load instruction.
 *
 * Encoding
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |    DR     |             PCoffset9             |
 *
 */
void	ld(uint16_t instr, t_vm *vm)
{
	uint16_t	dr;
	uint16_t	offset;

	dr = instr >> 9 & 7;
	offset = sign_extend(instr & 0x1ff, 9);
	vm->regs[dr] = mem_read(vm, vm->regs[R_PC + offset]);
	update_cond(vm, dr);
}

/* Load indirect. Reads the value stored in the address pointed to by
 * PC + PCoffset.
 *
 * Encoding
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |    DR     |             PCoffset9             |
 *
 */
void	ldi(uint16_t instr, t_vm *vm)
{
	uint16_t	dr;
	uint16_t	offset;

	dr = instr >> 9 & 7;
	offset = sign_extend(instr & 0x1ff, 9);
	vm->regs[dr] = mem_read(vm, mem_read(vm, vm->regs[R_PC + offset]));
	update_cond(vm, dr);
}

/* Load register.
 *
 * Encoding
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |    DR     |   BaseR   |        offset6        |
 *
 */
void	ldr(uint16_t instr, t_vm *vm)
{
	uint16_t	dr;
	uint16_t	br;
	uint16_t	offset;

	dr = instr >> 9 & 7;
	br = instr >> 6 & 7;
	offset = sign_extend(instr & 0x3f, 6);
	vm->regs[dr] = mem_read(vm, vm->regs[br] + offset);
	update_cond(vm, dr);
}

/* Load effective address.
 *
 * Encoding
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |    DR     |             PCoffset9             |
 *
 */
void	lea(uint16_t instr, t_vm *vm)
{
	uint16_t	dr;
	uint16_t	offset;

	dr = instr >> 9 & 7;
	offset = sign_extend(instr & 0x1ff, 9);
	vm->regs[dr] = mem_read(vm, vm->regs[R_PC] + offset);
	update_cond(vm, dr);
}
