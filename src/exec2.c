/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:48:20 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/17 16:51:18 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec2.h"
#include "exec3.h"

int	ft_close_wait(int outs[2], int pid1, int pid2)
{
	int	ret;

	close(outs[0]);
	close(outs[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &ret, 0);
	return (ft_status_exit_code(ret));
}

int	ft_pipe(t_tree *l, t_tree *r, t_env *env)
{
	int	outs[2];
	int	pid1;
	int	pid2;

	if (pipe(outs) < 0)
		return (1);
	pid1 = fork();
	if (pid1 == 0)
	{
		if (dup2(outs[1], 1) < 0)
			return (1);
		close(outs[0]);
		close(outs[1]);
		ft_exit(ft_exec(l, env), env);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		if (dup2(outs[0], 0) < 0)
			return (1);
		close(outs[0]);
		close(outs[1]);
		ft_exit(ft_exec(r, env), env);
	}
	return (ft_close_wait(outs, pid1, pid2));
}

int	ft_close_redirs(int size_redirs, int *fd_redirs)
{
	int	i;

	i = 0;
	while (i < size_redirs)
		close(fd_redirs[i++]);
	free(fd_redirs);
	return (0);
}

int	ft_finish_exec(t_exec *e)
{
	close(e->save_in);
	close(e->save_out);
	g_exit_code = e->ret;
	return (e->ret);
}

int	ft_redirs_helper(t_redirs *r, t_redir **redirs, char **env)
{
	while (redirs[r->i])
	{
		if (redirs[r->i]->hdoc_fd == -1)
		{
			redirs[r->i]->filename = ft_redir_expand(redirs[r->i]
					->filename, env);
			if (!redirs[r->i]->filename)
				return (ft_print_error());
			r->fd_redirs[r->i] = open(redirs[r->i]
					->filename, redirs[r->i]->option, 0644);
			if (r->fd_redirs[r->i] == -1)
				return (ft_close_error(r));
		}
		else
		{
			r->fd_redirs[r->i] = redirs[r->i]->hdoc_fd;
		}
		if (redirs[r->i]->fd == 0)
			r->last_in = r->fd_redirs[r->i];
		else
			r->last_out = r->fd_redirs[r->i];
		r->i++;
	}
	return (0);
}
