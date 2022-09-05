/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:30:45 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/05 10:35:16 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int	init_vm(t_vm *vm)
{
	vm->running = 1;
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
	vm->memory[PC_START + 1] = 0b1111000000100101;
}

static const t_operation	g_jumptable[16] = {
	branch,
	add,
	ld,
	st,
	jsr,
	and_comparison,
	ldr,
	str,
	rti,
	complement,
	ldi,
	sti,
	jump,
	0,
	lea,
	trap,
};

int	main(void)
{
	t_vm		vm;
	uint16_t	instr;
	uint16_t	op;

	if (init_vm(&vm) == -1)
		return (-1);
	load_program(&vm);
	while (vm.running)
	{
		instr = vm.memory[vm.regs[R_PC]];
		op = instr >> 12;
		vm.regs[R_PC]++;
		g_jumptable[op](instr, &vm);
	}
	return (0);
}
