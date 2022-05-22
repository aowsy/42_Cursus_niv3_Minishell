/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:51:39 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/03 16:55:02 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "exec.h"
# include "tree.h"
# include "built_ins.h"

void	ft_shell_cancel(int signum);
void	ft_nothing(int signum);
int		ft_exec_sigwrap(t_tree *t, t_env *env);
void	ft_term_unctrl(void);

#endif
