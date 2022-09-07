/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rti_instr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:11:09 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/04 22:13:07 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"

/* Return from interrupt. NOT IMPLEMENTED. */
void	rti(uint16_t instr, t_vm *vm)
{
	(void) vm;
	(void) instr;
}
