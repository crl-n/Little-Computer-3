/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:13:56 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/04 22:17:21 by carlnysten       ###   ########.fr       */
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

	sr = instr >> 9 & 7;
	offset = sign_extend(instr & 0x1ff, 9);
	vm->memory[vm->regs[R_PC] + offset] = vm->regs[sr];
}
