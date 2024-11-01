/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   T_ListUtils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:27:26 by nghaddar          #+#    #+#             */
/*   Updated: 2024/10/26 20:37:51 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_t_list	*init_t_list(void)
{
	t_t_list	*new_t_list;

	new_t_list = malloc(sizeof(t_t_list));
	if (!new_t_list)
		return (NULL);
	new_t_list->first = NULL;
	new_t_list->last = NULL;
	new_t_list->size = 0;
	return (new_t_list);
}

void	free_token_list(t_t_list *t_list_to_free)
{
	t_token	*token_cursor;
	t_token	*to_free;

	if (t_list_to_free)
	{
		token_cursor = t_list_to_free->first;
		while (token_cursor)
		{
			to_free = token_cursor;
			token_cursor = to_free->next;
			if (to_free->value)
				free(to_free->value);
			free(to_free);
		}
		free(t_list_to_free);
	}
}

t_token	*create_token(const char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->type = type;
	new_token->index = 0;
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	return (new_token);
}

void	add_token(t_t_list *t_list, t_token *new_token)
{
	if (!t_list || !new_token)
		return ;
	if (!t_list->first)
	{
		new_token->index = 0;
		t_list->first = new_token;
		t_list->last = new_token;
	}
	else
	{
		new_token->index = t_list->last->index + 1;
		new_token->prev = t_list->last;
		new_token->next = NULL;
		t_list->last->next = new_token;
		t_list->last = new_token;
	}
	t_list->size++;
}
