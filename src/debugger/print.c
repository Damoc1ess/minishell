/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:48:27 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/01 15:36:55 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/debugger.h"

static const char *color_codes[] = {
	GREEN, GREEN, YELLOW, YELLOW, YELLOW,
	YELLOW, YELLOW, CYAN, CYAN, CYAN,
	CYAN, MAGENTA, MAGENTA, MAGENTA, RED
};

void	print_token_type(t_token_type type)
{
	const char	*types[] = {
		"Command", "Argument", "Pipe", "Redirection In", "Redirection Out",
		"Append", "Heredoc", "Variable", "String", "And", "Or",
		"End of File", "Wildcard", "Expand", "Unknown token type"
	};
	int	index;

	if (type & TOKEN_COMMAND)
		index = 0;
	if (type & TOKEN_ARGUMENT)
		index = 1;
	if (type & TOKEN_PIPE)
		index = 2;
	if (type & TOKEN_REDIRECTION_IN)
		index = 3;
	if (type & TOKEN_REDIRECTION_OUT)
		index = 4;
	if (type & TOKEN_APPEND)
		index = 5;
	if (type & TOKEN_HEREDOC)
		index = 6;
	if (type & TOKEN_VARIABLE)
		index = 7;
	if (type & TOKEN_STRING)
		index = 8;
	if (type & TOKEN_AND)
		index = 9;
	if (type & TOKEN_OR)
		index = 10;
	if (type & TOKEN_EOF)
		index = 11;
	if (type & TOKEN_WILDCARDS)
		index = 12;
	if (type & TOKEN_EXPAND)
		index = 13;
	if (type & TOKEN_INCONNU)
		index = 14;
		
	printf("%s%s%s", color_codes[index], types[index], RESET);
}

void	print_t_list(t_t_list *t_list)
{
	t_token			*token_cursor;
	unsigned int	index;

	printf(CYAN "\n== TOKEN LIST (" YELLOW "%u" CYAN " tokens) ==\n" RESET, t_list->size);
	token_cursor = t_list->first;
	index = 0;
	while (token_cursor)
	{
		printf(BLUE "Token %u:\n" RESET, index);
		printf("  " MAGENTA "Type   : " RESET);
		print_token_type(token_cursor->type);
		printf("\n  " MAGENTA "Value  : " RESET "\"%s\"", token_cursor->value);
		printf(CYAN "-----------------------------\n" RESET);
		token_cursor = token_cursor->next;
		index++;
	}
	printf(CYAN "== END OF TOKEN LIST ==\n\n" RESET);
}

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

static const char	*get_color(int level)
{
	const char	*colors[] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

	return (colors[level % 7]);
}

static void	print_indentation(int level)
{
	int	i;

	i = 0;
	while (i < level)
	{
		ft_putstr("    ");
		i++;
	}
}

static void	print_node_info(t_ast_node *node, int level)
{
	const char	*color;

	color = get_color(level);
	ft_putstr(color);
	if (node->type == AST_COMMAND)
	{
		ft_putstr("COMMAND: ");
		if (node->argv)
		{
			int	i = 0;
			while (node->argv[i])
			{
				ft_putstr(node->argv[i]);
				if (node->argv[i + 1])
					ft_putstr(" ");
				i++;
			}
		}
		ft_putstr("\n");
	}
	else if (node->type == AST_PIPE)
		ft_putstr("PIPE\n");
	else if (node->type == AST_AND)
		ft_putstr("AND (&&)\n");
	else if (node->type == AST_OR)
		ft_putstr("OR (||)\n");
	else if (node->type == AST_REDIRECTION_IN)
		ft_printf("REDIR_IN: <%s\n", node->filename);
	else if (node->type == AST_REDIRECTION_OUT)
		ft_printf("REDIR_OUT: >%s\n", node->filename);
	else if (node->type == AST_REDIRECTION_APPEND)
		ft_printf("REDIR_APPEND: >>%s\n", node->filename);
	else if (node->type == AST_REDIRECTION_HEREDOC)
		ft_printf("HEREDOC: <<%s\n", node->filename);
	ft_putstr(RESET);
}

void	print_ast(t_ast_node *node, int level)
{
	if (!node)
		return ;
	print_indentation(level);
	print_node_info(node, level);
	if (node->left)
		print_ast(node->left, level + 1);
	if (node->right)
		print_ast(node->right, level + 1);
}