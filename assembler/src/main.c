/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:28:45 by cnysten           #+#    #+#             */
/*   Updated: 2022/09/07 15:10:52 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

#define SEPARATORS " \n\t"

char	*read_file(char *filename)
{
	FILE	*file;
	size_t	filesize;
	char	*contents;

	file = fopen(filename, "r");
	if (!file)
		return (puts("Error: could not open file\n"), NULL);
	fseek(file, 0L, SEEK_END);
	filesize = ftell(file);
	fseek(file, 0L, SEEK_SET);
	/* printf("Filesize: %zu\n", filesize); */
	contents = malloc(filesize);
	if (!contents)
		return (NULL);
	fread(contents, sizeof (char), filesize, file);
	return (contents);
}

char	**lex(char *contents)
{
	char	**lexemes;
	char	*str;
	size_t	size;
	size_t	len;

	size = 1;
	len = 0;
	lexemes = malloc(size * sizeof (char *));
	str = strtok(contents, SEPARATORS);
	while (str != NULL)
	{
		/* printf("'%s', ", str); */
		if (len == size)
		{
			lexemes = realloc(lexemes, size * 2 * sizeof (char *));
			size *= 2;
		}
		lexemes[len++] = str;
		str = strtok(NULL, SEPARATORS);
	}
	for (size_t i = 0; i < len; i++)
		printf("'%s', ", lexemes[i]);
	return (lexemes);
}

t_token	*tokenize(char **lexemes)
{
	(void) lexemes;
	return (NULL);
}

uint16_t	*map_to_instructions(t_token *tokens)
{
	(void) tokens;
	return (NULL);
}

int	main(int argc, char **argv)
{
	char		*contents;
	uint16_t	*output;

	if (argc < 2)
		return (puts("Usage: little-assembler [asm-file]\n"), 0);
	contents = read_file(argv[1]);
	if (!contents)
		return (-1);
	/* printf("%s", contents); */
	output = map_to_instructions(tokenize(lex(contents)));
	return (0);
}
