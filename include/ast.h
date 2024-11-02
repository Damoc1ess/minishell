/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:36:31 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/02 13:41:58 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"
# include "debugger.h"

typedef enum e_ast_node_type
{
    AST_COMMAND,
    AST_PIPE,
    AST_AND,
    AST_OR,
    AST_REDIRECTION_IN,
    AST_REDIRECTION_OUT,
    AST_REDIRECTION_APPEND,
    AST_REDIRECTION_HEREDOC
}   t_ast_node_type;

typedef struct s_ast_node
{
    t_ast_node_type     type;
    char                **argv;
    char                *filename;
    struct s_ast_node   *left;
    struct s_ast_node   *right;
}   t_ast_node;

t_ast_node  *create_ast_node(t_ast_node_type type);
void        add_argument(t_ast_node *node, char *argument);
void        free_ast(t_ast_node *node);

//parser
t_ast_node  *ast_parser(t_t_list *token_list);
t_ast_node *parse_parentheses(t_token **current_token);

//execution
int execute_ast(t_ast_node *node, t_sh *shell);

#endif
