/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:08:35 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/02 11:55:16 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool check_path(char *path, char *command)
{
	char *full_path;
	int exists;

	full_path = ft_strjoin(path, "/");
	if (!full_path)
		return (false);
	full_path = ft_strjoin_free(full_path, command);
	if (!full_path)
		return (false);
	exists = (access(full_path, X_OK) == 0);
	free(full_path);
	return (exists);
}

bool command_exists(char *command, char **envp)
{
	char *path;
	char **paths;
	int i;
	bool found;

	path = get_env_value("PATH", envp);
	if (!path)
		return (false);
	paths = ft_split(path, ':');
	if (!paths)
		return (false);
	i = 0;
	found = false;
	while (paths[i] && !found)
	{
		found = check_path(paths[i], command);
		i++;
	}
	ft_free_split(paths);
	return (found);
}

void h_par(char c, uint16_t *i, t_t_list *t_list)
{
	if (c == '(')
		add_token(t_list, create_token("(", TOKEN_LPAREN));
	else if (c == ')')
		add_token(t_list, create_token(")", TOKEN_RPAREN));
	(*i)++;
}
