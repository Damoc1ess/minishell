/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:57:07 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/02 12:05:16 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGGER_H
# define DEBUGGER_H

# include "minishell.h"
# include "ast.h"

# define RESET		"\033[0m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"

void	print_t_list(t_t_list *list);
void	print_env(char **envp);
void    print_ast(t_ast_node *node, int level);


#endif
