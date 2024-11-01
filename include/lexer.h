/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:09:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/31 11:50:49 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "minishell.h"

typedef enum e_token_type
{
	TOKEN_COMMAND = (uint8_t)1 << 0,
	TOKEN_ARGUMENT = (uint8_t)1 << 1,
	TOKEN_PIPE = (uint8_t)1 << 2,
	TOKEN_REDIRECTION_IN = (uint8_t)1 << 3,
	TOKEN_REDIRECTION_OUT = (uint8_t)1 << 4,
	TOKEN_APPEND = (uint8_t)1 << 5,
	TOKEN_HEREDOC = (uint8_t)1 << 6,
	TOKEN_VARIABLE = (uint8_t)1 << 7,
	TOKEN_STRING = (uint8_t)1 << 8,
	TOKEN_AND = (uint8_t)1 << 9,
	TOKEN_OR = (uint8_t)1 << 10,
	TOKEN_EOF = (uint8_t)1 << 11,
	TOKEN_WILDCARDS = (uint8_t)1 << 12,
	TOKEN_EXPAND = (uint8_t)1 << 13,
	TOKEN_INCONNU = (uint8_t)1 << 14,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	uint16_t			index;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_token_list
{
	struct s_token		*first;
	struct s_token		*last;
	unsigned int		size;
}	t_t_list;

// T_List & token utils
t_t_list		*init_t_list(void);
void			free_token_list(t_t_list *t_list);
t_token			*create_token(const char *value, t_token_type type);
void			add_token(t_t_list *t_list, t_token *new_token);

t_t_list		*lexer(char *input, t_sh *shell);

// lexer utils1
void			h_pipe(char *input, uint16_t *i, t_t_list *t_list);
void			h_rout(char *input, uint16_t *i, t_t_list *t_list);
void			h_rin(char *input, uint16_t *i, t_t_list *t_list);
void			h_s_q(char *input, uint16_t *i, t_t_list *t_list);
void			h_d_q(char *input, uint16_t *i, t_t_list *t_list, t_sh *shell);

// lexer utils2
void			h_cmd_arg(char *input, uint16_t *i, t_t_list *t_list, char **invp);
void			handle_and(uint16_t *i, t_t_list *t_list);
void			handle_wildcards(uint16_t *i, t_t_list *t_list);

// lexer utils3
void			h_exp(char *input, uint16_t *i, t_t_list *t_list, t_sh *shell);
char			*parse_env_var(char *input, uint16_t *i, t_sh *shell);

// lexer utils4
void			handle_heredoc(t_token *heredoc_token, char *delimiter);
void			handle_inconnu(char *input, uint16_t *i, t_t_list *t_list);
void			handle_builtin_command(char *input, uint16_t *i, t_t_list *t_list);

//lexxer utils5
bool		command_exists(char *command, char **envp);
#endif
