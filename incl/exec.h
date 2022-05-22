/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:22:18 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/04/27 15:42:07 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# include "varstar.h"
# include "tree.h"
# include "built_ins.h"
# include "exec_utils.h"
# include "resource_management.h"
# include "exit.h"

typedef struct s_exec
{
	char	*path_command;
	int		pid;
	int		ret;
	int		waitstatus;
	int		save_out;
	int		save_in;
}	t_exec;

typedef struct s_redirs
{
	int	*fd_redirs;
	int	size_redirs;
	int	last_in;
	int	last_out;
	int	i;
}	t_redirs;

int	ft_exec(t_tree *t, t_env *env);

#endif
