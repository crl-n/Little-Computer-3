/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:30:45 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/04 15:22:04 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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

int	init_vm(t_vm *vm)
{
	vm->memory = malloc(MEMORY_MAX * sizeof (uint16_t));
	if (!vm->memory)
		return (-1);
	bzero(vm->regs, sizeof (uint16_t) * 11);
	vm->regs[R_PC] = PC_START;
	vm->regs[R_COND] = COND_POS;
	return (0);
}

void	load_program(t_vm *vm)
{
	vm->memory[PC_START] = 0b0001001010100001;
}

static const t_operation	g_jumptable[16] = {
	0,
	add,
};

int	main(void)
{
	t_vm		vm;
	uint16_t	instr;
	uint16_t	op;

	if (init_vm(&vm) == -1)
		return (-1);
	load_program(&vm);
	while (1)
	{
		instr = vm.memory[vm.regs[R_PC]];
		op = instr >> 12;
		vm.regs[R_PC]++;
		g_jumptable[op](instr, &vm);
	}
	return (0);
}
