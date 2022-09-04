/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lc3vm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:31:40 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/04 19:49:29 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LC3VM_H
# define LC3VM_H

# include <stdint.h>

# define MEMORY_MAX (1 << 16)
# define PC_START 0x3000

enum e_registry
{
	R_R0 = 0,
	R_R1,
	R_R2,
	R_R3,
	R_R4,
	R_R5,
	R_R6,
	R_R7,
	R_PC,
	R_COND,
	R_COUNT
};

enum e_opcode
{
	OP_BR = 0,
	OP_ADD,
	OP_LD,
	OP_ST,
	OP_JSR,
	OP_AND,
	OP_LDR,
	OP_STR,
	OP_RTI,
	OP_NOT,
	OP_LDI,
	OP_STI,
	OP_JMP,
	OP_RES,
	OP_LEA,
	OP_TRAP,
};

enum e_cond
{
	COND_POS = 1 << 0,
	COND_ZERO = 1 << 1,
	COND_NEG = 1 << 2,
};

enum e_trapcode
{
	TRAP_GETC = 0x20,
	TRAP_OUT = 0x21,
	TRAP_PUTS = 0x22,
	TRAP_IN = 0x23,
	TRAP_PUTSP = 0x24,
	TRAP_HALT = 0x25,
};

typedef struct s_vm
{
	uint16_t	*memory;
	uint16_t	regs[11];
	uint8_t		running;
}	t_vm;

typedef void (*t_operation)(uint16_t, t_vm *);

void		add(uint16_t instr, t_vm *vm);
void		trap(uint16_t instr, t_vm *vm);
uint16_t	sign_extend(uint16_t val, int bit_count);
void		update_cond(t_vm *vm, uint16_t r);

#endif
