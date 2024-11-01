/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:09:34 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/27 17:31:42 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

typedef struct s_shell
{
	int		exit_status;
	char	**envp;
}				t_sh;

void	update_exit_status(t_sh *shell, int status);
void	initialize_shell(t_sh *shell, char **envp);
char	*get_env_value(const char *name, char **envp);

#endif
