/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:30:45 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/03 21:02:07 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	t_vm	vm;

	vm.memory = malloc(MEMORY_MAX * sizeof (uint16_t));
	if (!vm.memory)
		return (-1);
	bzero(vm.regs, sizeof (uint16_t) * 11);
	return (0);
}
