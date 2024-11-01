/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:36:26 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/30 11:43:03 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_brace_expand(char *input, uint16_t *i, t_t_list *t_list)
{
	char	buffer[256];
	size_t	j;
	char	*word;

	j = 0;
	(*i)++;
	while (input[*i] && input[*i] != '}')
	{
		if (j < sizeof(buffer) - 1)
			buffer[j++] = input[*i];
		(*i)++;
	}
	if (input[*i] != '}')
	{
		fprintf(stderr, "Error: Missing closing brace\n");
		return ;
	}
	(*i)++;
	buffer[j] = '\0';
	word = ft_strtok(buffer, " ");
	while (word != NULL)
	{
		add_token(t_list, create_token(word, TOKEN_EXPAND));
		word = ft_strtok(NULL, " ");
	}
}

void	h_alnum_ex(char *input, uint16_t *i, t_t_list *token_list, char **envp)
{
	char			buffer[256];
	unsigned int	j;
	char			*value;

	j = 0;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
	{
		if (j < sizeof(buffer) - 1)
			buffer[j++] = input[*i];
		(*i)++;
	}
	buffer[j] = '\0';
	value = get_env_value(buffer, envp);
	if (value)
		add_token(token_list, create_token((value), TOKEN_EXPAND));
	else
		add_token(token_list, create_token((""), TOKEN_EXPAND));
}

void	h_exp(char *input, uint16_t *i, t_t_list *t_list, t_sh *shell)
{
	char	*status;

	(*i)++;
	if (input[*i] == '?')
	{
		status = ft_itoa(shell->exit_status);
		add_token(t_list, create_token(status, TOKEN_EXPAND));
		(*i)++;
	}
	else if (input[*i] == '{')
		handle_brace_expand(input, i, t_list);
	else
		h_alnum_ex(input, i, t_list, shell->envp);
}

char	*parse_env_var(char *input, uint16_t *i, t_sh *shell)
{
	char	var_name[256];
	char	*env_value;
	size_t	var_len;

	var_len = 0;
	while (input[*i] && ft_isalnum(input[*i]) && var_len < sizeof(var_name) - 1)
	{
		var_name[var_len] = input[*i];
		var_len++;
		(*i)++;
	}
	var_name[var_len] = '\0';
	env_value = get_env_value(var_name, shell->envp);
	if (env_value)
		return (env_value);
	else
		return ("");
}
