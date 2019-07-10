/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdamion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:43:25 by gdamion-          #+#    #+#             */
/*   Updated: 2019/07/09 18:57:01 by gdamion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "com.h"
# include "asm_error.h"
# include "asm_ops.h"

char					g_buf[CHAMP_MAX_SIZE * 2 + 1];

typedef enum			e_type
{
	REGISTER = 1,
	DIRECT,
	COMMAND,
	INDIRECT,
	STRING,
	LABEL,
	INSTRUCTION,
	DIRECT_LABEL,
	INDIRECT_LABEL,
	SEPARATOR,
	NEW_LINE,
	END
}						t_type;

typedef struct			s_token
{
	int					x;
	int					y;
	t_type				type;
	struct s_token		*next;
	struct s_token		*prev;
	char				*content;
}						t_token;

typedef struct			s_label
{
	int					x;
	int					y;
	char				*name;
	t_token				*point;
	struct s_label		*next;
	struct s_label		*prev;
}						t_label;

typedef struct			s_data
{
	int					x;
	int					y;
	int					fd;
	char				*f_name;
	t_token				*token;
	t_label				*label;
}						t_data;

// typedef struct			s_op
// {
// 	char				type_a1[2];
// 	char				type_a2[2];
// 	char				type_a3[2];

// }

# define Q(c) (c == '\0')
# define W(c) (c == '\n')
# define E(c) (c == '\"')
# define R(c) (c == DIRECT_CHAR)
# define T(c) (c == SEPARATOR_CHAR)
# define Y(c) (c == COMMENT_CHAR)
# define U(c) (SP(c))

# define DELIMITER(c) (Q(c) || W(c) || E(c) || R(c) || T(c) || Y(c) || U(c))

# define INIT_DATA (!(temp = (t_data*)ft_memalloc(sizeof(t_data))))
# define INIT_TOKEN (!(new = (t_token*)ft_memalloc(sizeof(t_token))))
# define INIT_LABEL (!(new = (t_label*)ft_memalloc(sizeof(t_label))))

void		read_file(char *filename);
void		data_init(t_data **data, int fd);
void		lexical_analyzer(t_data *data);
int			skip_whitespaces(char *line, int cursor);
int			skip_comment(char *line, int cursor);
void		token_add(t_data *data, t_type type);
void		label_add(t_data *data);
_Bool		is_reg(char *line, int len);
void		syntax_analiser(t_data *data);


void		error(char *err_place, int str_no, int col_no, t_data *data);
void		errorr(char *err_place, int str_no, int col_no);

#endif
