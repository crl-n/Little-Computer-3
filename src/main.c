/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:30:45 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/06 00:28:38 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const t_operation	g_jumptable[16] = {
	br,
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
	jmp,
	0,
	lea,
	trap,
};

void	handle_interrupt(int signal)
{
	(void) signal;
	restore_input_buffering();
	puts("\n");
	exit(-2);
}

int	init(t_vm *vm)
{
	vm->running = 1;
	vm->memory = malloc(MEMORY_MAX * sizeof (uint16_t));
	if (!vm->memory)
		return (-1);
	bzero(vm->regs, sizeof (uint16_t) * 11);
	vm->regs[R_PC] = PC_START;
	vm->regs[R_COND] = COND_POS;
	signal(SIGINT, handle_interrupt);
	disable_input_buffering();
	return (0);
}

void	load_program(t_vm *vm, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!read_image(argv[i], vm))
		{
			printf("Failed to load image: %s\n", argv[i]);
			exit(-1);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_vm		vm;
	uint16_t	instr;
	uint16_t	op;

	if (argc < 2)
		return (puts("Usage: lc3 [image-file1] ...\n"), 0);
	if (init(&vm) == -1)
		return (-1);
	load_program(&vm, argc, argv);
	while (vm.running)
	{
		instr = mem_read(&vm, vm.regs[R_PC]);
		op = instr >> 12;
		vm.regs[R_PC]++;
		g_jumptable[op](instr, &vm);
	}
	restore_input_buffering();
	return (0);
}
