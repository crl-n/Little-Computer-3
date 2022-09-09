/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:28:45 by cnysten           #+#    #+#             */
/*   Updated: 2022/09/09 11:50:43 by cnysten          ###   ########.fr       */
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

t_str_arr	lex(char *contents)
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
	return ((t_str_arr){lexemes, len});
}

int	is_opcode(char *token_str)
{
	static char	*op_identifiers[] = {"ADD", "AND", "BR", "JMP",
									"JSR", "LD", "LDI", "LDR",
									"LEA", "NOT", "RET", "RTI",
									"ST", "STI", "STR", "TRAP"};
	for (int i = 0; i < 16; i++)
	{
		if (strcmp(token_str, op_identifiers[i]) == 0)
			return (1);
	}
	return (0);
}

t_token	*tokenize(t_str_arr arr)
{
	t_token	*tokens;
	char	**lexemes;
	size_t	len;

	lexemes = arr.strs;
	len = arr.len;
	tokens = malloc(len * sizeof (t_token));
	if (!tokens)
		return (NULL);
	for (size_t i = 0; i < len; i++)
	{
		printf("lexemes[%zu]: %s\n", i, lexemes[i]);
		if (lexemes[i][0] == ';')
			tokens[i] = (t_token){COMMENT, lexemes[i]};
		else if (lexemes[i][0] == '.')
			tokens[i] = (t_token){PSEUDOOP, lexemes[i]};
		else if (is_opcode(lexemes[0]))
			tokens[i] = (t_token){OPCODE, lexemes[i]};
	}
	printf("\n\n\n");
	for (size_t i = 0; i < len; i++)
		printf("Type %d: '%s', ", tokens[i].type, tokens[i].lexeme);
	return (tokens);
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
