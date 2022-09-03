/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lc3vm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:31:40 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/03 21:01:51 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LC3VM_H
# define LC3VM_H

# include <stdint.h>

# define MEMORY_MAX (1 << 16)

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

typedef struct s_vm
{
	uint16_t	*memory;
	uint16_t	regs[11];
}	t_vm;

#endif
