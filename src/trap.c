/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:29:17 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/05 12:37:45 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"
#include <stdio.h>
#include <unistd.h>

/* Read a single ASCII character */
void	trap_getc(t_vm *vm)
{
	vm->regs[R_R0] = (uint16_t) getchar();
	update_cond(vm, R_R0);
}

/* Write a single ASCII character */
void	trap_out(t_vm *vm)
{
	uint16_t	c;

	c = vm->regs[R_R0] & 0xff;
	putc((char) c, stdout);
}

/* Writes a null-terminated string of ASCII characters to the STDOUT.
 * Each character is stored not as a byte, but a uint16_t */
void	trap_puts(t_vm *vm)
{
	uint16_t	*c;

	c = vm->memory + vm->regs[R_R0];
	while (*c)
	{
		putc((char) *c, stdout);
		c++;
	}
	fflush(stdout);
}

/* Prompts the user for a single ASCII character */
void	trap_in(t_vm *vm)
{
	char	c;

	puts("Enter a character: ");
	c = getchar();
	putc(c, stdout);
	fflush(stdout);
	vm->regs[R_R0] = (uint16_t) c;
	update_cond(vm, R_R0);
}

/* Writes a null-terminated string of ASCII characters to the STDOUT.
 * The characters are stored in 16-bit unsigned integers.
 * Each integer stores 2 chars. The char in bits 7:0 is printed first,
 * then 15:8. */
void	trap_putsp(t_vm *vm)
{
	uint16_t	*c;

	c = vm->memory + vm->regs[R_R0];
	while (*c)
	{
		putc((char)((*c) & 0xff), stdout);
		if ((*c) & 0xff00)
			putc((char)((*c) >> 8), stdout);
		c++;
	}
	fflush(stdout);
}

/* Encoding
 *
 * |15 |14 |13 |12 |11 |10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |    OPCODE     |       -       |           TRAPCODE            |
 *
 */
void	trap(uint16_t instr, t_vm *vm)
{
	uint16_t	trapcode;

	trapcode = instr & 0xff;
	if (trapcode == TRAP_GETC)
		trap_getc(vm);
	else if (trapcode == TRAP_OUT)
		trap_out(vm);
	else if (trapcode == TRAP_PUTS)
		trap_puts(vm);
	else if (trapcode == TRAP_IN)
		trap_in(vm);
	else if (trapcode == TRAP_PUTSP)
		trap_putsp(vm);
	else if (trapcode == TRAP_HALT)
		vm->running = 0;
}
