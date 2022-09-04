/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:00:42 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/04 22:07:47 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"

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
