/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:54:49 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 17:11:19 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec2.h"
#include "exec3.h"
#include <signal.h>

int	ft_status_exit_code(int ws)
{
	if (WIFSIGNALED(ws))
	{
		ws = WTERMSIG(ws);
		if (ws == SIGINT)
			printf("Interrupted\n");
		else if (ws == SIGQUIT)
			printf("Quit\n");
		return (128 + ws);
	}
	if (WIFEXITED(ws))
		return (WEXITSTATUS(ws));
	else
		return (1);
}

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		if (*str1 != *str2)
			return (0);
		str1++;
		str2++;
	}
	return (1);
}

int	ft_close_error(t_redirs *r)
{
	ft_close_redirs(r->i, r->fd_redirs);
	ft_putstr_fd("Error: non existent or non accessible file.\n", 2);
	return (1);
}

int	ft_print_error(void)
{
	ft_putstr_fd("Error: ambiguous redirections.\n", 2);
	return (1);
}
