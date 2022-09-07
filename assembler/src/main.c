/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:28:45 by cnysten           #+#    #+#             */
/*   Updated: 2022/09/07 13:58:29 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char	*read_file(char *filename)
{
	FILE	*file;
	size_t	filesize;
	char	*contents;
	/* char	buffer[512]; */

	file = fopen(filename, "r");
	if (!file)
		return (puts("Error: could not open file\n"), NULL);
	fseek(file, 0L, SEEK_END);
	filesize = ftell(file);
	fseek(file, 0L, SEEK_SET);
	printf("Filesize: %zu\n", filesize);
	contents = malloc(filesize);
	if (!contents)
		return (NULL);
	fread(contents, sizeof (char), filesize, file);
	return (contents);
}

int	main(int argc, char **argv)
{
	char	*contents;

	if (argc < 2)
		return (puts("Usage: little-assembler [asm-file]\n"), 0);
	contents = read_file(argv[1]);
	if (!contents)
		return (-1);
	printf("%s", contents);
	return (0);
}
