/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:54:39 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:16:35 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC3_H
# define EXEC3_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# include "exec.h"
# include "varstar.h"
# include "tree.h"
# include "built_ins.h"
# include "exec_utils.h"
# include "resource_management.h"
# include "exit.h"

int	ft_close_error(t_redirs *r);
int	ft_print_error(void);
int	ft_strcmp(char *str1, char *str2);
int	ft_status_exit_code(int ws);

#endif
