/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:49:12 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/04/27 16:21:31 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC2_H
# define EXEC2_H

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

int		ft_close_redirs(int size_redirs, int *fd_redirs);
int		ft_pipe(t_tree *l, t_tree *r, t_env *env);
int		ft_finish_exec(t_exec *e);
int		ft_redirs_helper(t_redirs *r, t_redir **redirs, char **env);

#endif
