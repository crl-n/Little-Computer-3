/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cond.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:43:55 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/04 19:49:19 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"

void	update_cond(t_vm *vm, uint16_t r)
{
	if (vm->regs[r] == 0)
		vm->regs[R_COND] = COND_ZERO;
	else if (vm->regs[r] < 0)
		vm->regs[R_COND] = COND_NEG;
	else
		vm->regs[R_COND] = COND_POS;
}
