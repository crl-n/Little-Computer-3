/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <cnysten@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:16:33 by cnysten           #+#    #+#             */
/*   Updated: 2022/09/07 13:55:38 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

enum e_type
{
	LABEL,
	OPCODE,
	OPERAND,
	DIRECTIVE,
	COMMENT,
};

typedef struct s_token
{
	enum e_type	type;
	char 		*lexeme;
}	t_token;

#endif
