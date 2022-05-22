/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:47:10 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/03 17:08:27 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	ft_shell_cancel(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_nothing(int signum)
{
	(void) signum;
}

int	ft_exec_sigwrap(t_tree *t, t_env *env)
{
	int	ret;

	signal(SIGQUIT, ft_nothing);
	signal(SIGINT, ft_nothing);
	ret = ft_exec(t, env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_shell_cancel);
	return (ret);
}

void	ft_term_unctrl(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
}
