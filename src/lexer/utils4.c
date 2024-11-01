/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:54:03 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/31 11:50:58 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc(t_token *heredoc_token, char *delimiter)
{
	int		fd;
	char	*line;

	fd = open("heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	free(heredoc_token->value);
	heredoc_token->value = ft_strdup("heredoc.txt");
}

void	handle_inconnu(char *input, uint16_t *i, t_t_list *t_list)
{
	char	buffer[2];

	buffer[0] = input[*i];
	buffer[1] = '\0';
	add_token(t_list, create_token(buffer, TOKEN_INCONNU));
	(*i)++;
}

void	handle_builtin_command(char *input, uint16_t *i, t_t_list *t_list)
{
	char	buffer[256];
	int		j;

	j = 0;
	while (input[*i] && !ft_isspace(input[*i])
		&& input[*i] != '|' && input[*i] != '>'
		&& input[*i] != '<' && j < (int) sizeof(buffer) - 1)
	{
		buffer[j++] = input[(*i)++];
	}
	buffer[j] = '\0';
	add_token(t_list, create_token(buffer, TOKEN_COMMAND));
}
