/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:05:40 by carlnysten        #+#    #+#             */
/*   Updated: 2022/09/06 09:08:48 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"
#include <unistd.h>

struct termios	original_tio;
struct termios	new_tio;

void	disable_input_buffering(void)
{
	tcgetattr(STDIN_FILENO, &original_tio);
	new_tio = original_tio;
	new_tio.c_lflag &= ~ICANON & ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void	restore_input_buffering(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

uint16_t	check_key(void)
{
	struct timeval	timeout;
	fd_set			readfds;

	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	return (select(1, &readfds, NULL, NULL, &timeout) != 0);
}

uint16_t	mem_read(t_vm *vm, uint16_t addr)
{
	if (addr == MR_KBSR)
	{
		if (check_key())
		{
			vm->memory[MR_KBSR] = (1 << 15);
			vm->memory[MR_KBDR] = getchar();
		}
		else
			vm->memory[MR_KBSR] = 0;
	}
	return (vm->memory[addr]);
}

void	mem_write(t_vm *vm, uint16_t addr, uint16_t val)
{
	vm->memory[addr] = val;
}
