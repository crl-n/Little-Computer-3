/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:03:20 by cnysten           #+#    #+#             */
/*   Updated: 2022/09/05 13:22:52 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lc3vm.h"
#include <stdio.h>

/* Converts a little-endian value to big-endian. */
uint16_t	swap16(uint16_t x)
{
	return (x << 8 | x >> 8);
}

/* Opens an image file and writes all contained instructions to memory. */
void	read_image_file(FILE *file, t_vm *vm)
{
	uint16_t	origin;
	uint16_t	max_read;
	uint16_t	*ptr;
	size_t		bytes_read;

	fread(&origin, sizeof (origin), 1, file);
	origin = swap16(origin);
	max_read = MEMORY_MAX - origin;
	ptr = vm->memory + origin;
	bytes_read = fread(ptr, sizeof (uint16_t), max_read, file);
	while (bytes_read-- > 0)
	{
		*ptr = swap16(*ptr);
		ptr++;
	}
}

/* Convenience function. Takes a path to a image file, opens it 
 * and calls read_image_file() */
int	read_image(const char *path, t_vm *vm)
{
	FILE	*file;

	file = fopen(path, "rb");
	if (!file)
		return (0);
	read_image_file(file, vm);
	fclose(file);
	return (1);
}

