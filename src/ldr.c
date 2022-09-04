/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 21:45:29 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/04 21:50:07 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"

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
