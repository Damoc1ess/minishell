/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:12:45 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/02 14:46:37 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast_node *parse_command(t_token **current_token);
t_ast_node *parse_pipeline(t_token **current_token);
t_ast_node *parse_and_or_sequence(t_token **current_token);

t_ast_node *ast_parser(t_t_list *token_list)
{
	t_token *current_token;
	t_ast_node *ast_root;

	current_token = token_list->first;
	ast_root = parse_and_or_sequence(&current_token);
	return (ast_root);
}

t_ast_node *parse_and_or_sequence(t_token **current_token)
{
	t_ast_node *left;
	t_ast_node *node;
	t_token *token;

	left = parse_pipeline(current_token);
	while (*current_token && ((*current_token)->type == TOKEN_AND || (*current_token)->type == TOKEN_OR))
	{
		token = *current_token;
		*current_token = (*current_token)->next;
		node = create_ast_node(token->type == TOKEN_AND ? AST_AND : AST_OR);
		node->left = left;
		node->right = parse_pipeline(current_token);
		left = node;
	}
	return (left);
}

t_ast_node *parse_pipeline(t_token **current_token)
{
	t_ast_node *left;
	t_ast_node *node;

	left = parse_parentheses(current_token);
	while (*current_token && (*current_token)->type == TOKEN_PIPE)
	{
		*current_token = (*current_token)->next;
		node = create_ast_node(AST_PIPE);
		node->left = left;
		node->right = parse_parentheses(current_token);
		left = node;
	}
	return (left);
}

void parse_redirections(t_token **current_token, t_ast_node *command_node)
{
	t_token *token;
	t_ast_node *redir_node;
	t_ast_node *tmp;

	while (*current_token && ((*current_token)->type == TOKEN_REDIRECTION_IN 
		|| (*current_token)->type == TOKEN_REDIRECTION_OUT 
		|| (*current_token)->type == TOKEN_APPEND 
		|| (*current_token)->type == TOKEN_HEREDOC))
	{
		token = *current_token;
		*current_token = (*current_token)->next;
		if ((!*current_token 
		|| (*current_token)->type != TOKEN_ARGUMENT)
		&& !(*current_token)->type != TOKEN_HEREDOC )
		{
			printf("minishell: curent_token: No such file or directory\n ici\n");
			return;
		}
		redir_node = create_ast_node(AST_REDIRECTION_IN);
		if (token->type == TOKEN_REDIRECTION_OUT)
			redir_node = create_ast_node(AST_REDIRECTION_OUT);
		else if (token->type == TOKEN_APPEND)
			redir_node = create_ast_node(AST_REDIRECTION_APPEND);
		else if (token->type == TOKEN_HEREDOC)
			redir_node = create_ast_node(AST_REDIRECTION_HEREDOC);
		redir_node->filename = ft_strdup((*current_token)->value);
		*current_token = (*current_token)->next;
		if (!command_node->left)
			command_node->left = redir_node;
		else
		{
			tmp = command_node->left;
			while (tmp->left)
				tmp = tmp->left;
			tmp->left = redir_node;
		}
	}
}

t_ast_node *parse_command(t_token **current_token)
{
	t_ast_node *node;

	if (!*current_token)
		return (NULL);
	node = create_ast_node(AST_COMMAND);
	while (*current_token && ((*current_token)->type == TOKEN_COMMAND || (*current_token)->type == TOKEN_ARGUMENT || (*current_token)->type == TOKEN_STRING || (*current_token)->type == TOKEN_EXPAND))
	{
		add_argument(node, (*current_token)->value);
		*current_token = (*current_token)->next;
	}
	parse_redirections(current_token, node);
	return (node);
}

t_ast_node *parse_parentheses(t_token **current_token)
{
	t_ast_node *node;

	if ((*current_token)->type == TOKEN_LPAREN)
	{
		*current_token = (*current_token)->next;
		node = parse_and_or_sequence(current_token);
		if (!(*current_token) || (*current_token)->type != TOKEN_RPAREN)
		{
			fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n",
					(*current_token) ? (*current_token)->value : "newline");
			return NULL;
		}
		*current_token = (*current_token)->next;
		return node;
	}
	else
	{
		return parse_command(current_token);
	}
}
