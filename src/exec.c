/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:44:58 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/17 16:54:20 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec2.h"
#include "exec3.h"

int	ft_and(t_tree *l, t_tree *r, t_env *env)
{
	int	ret_l;
	int	ret_r;

	ret_l = ft_exec(l, env);
	if (ret_l == 0)
	{
		ret_r = ft_exec(r, env);
		return (ret_r);
	}
	return (ret_l);
}

int	ft_or(t_tree *l, t_tree *r, t_env *env)
{
	int	ret;

	ret = ft_exec(l, env);
	if (ret == 0)
		return (0);
	ret = ft_exec(r, env);
	return (ret);
}

int	ft_exec_command(char **args, t_env *env)
{
	t_exec	e;

	if (!args[0])
		return (0);
	e.ret = ft_dispatcher(args[0], args + 1, env);
	if (e.ret != E_NOT_BUILT_IN)
		return (e.ret);
	e.path_command = ft_get_path(args[0], env->e_tab);
	if (!e.path_command)
	{
		ft_putstr_fd("Error: command not found\n", 2);
		return (127);
	}
	e.pid = fork();
	if (e.pid == 0)
	{
		execve(e.path_command, args, env->e_tab);
		perror(e.path_command);
		free(e.path_command);
		ft_exit(127, env);
	}
	wait(&e.waitstatus);
	free(e.path_command);
	e.ret = ft_status_exit_code(e.waitstatus);
	return (e.ret);
}

int	ft_redirs(t_redir **redirs, char **env)
{
	t_redirs	r;

	r.last_in = 0;
	r.last_out = 1;
	if (!redirs)
		return (0);
	r.size_redirs = ft_get_size(redirs);
	r.fd_redirs = malloc(r.size_redirs * sizeof(int));
	if (!r.fd_redirs)
		return (1);
	r.i = 0;
	if (ft_redirs_helper(&r, redirs, env))
		return (1);
	if (dup2(r.last_in, 0) < 0)
		return (1);
	if (dup2(r.last_out, 1) < 0)
		return (1);
	return (ft_close_redirs(r.size_redirs, r.fd_redirs));
}

int	ft_exec(t_tree *t, t_env *env)
{
	t_exec	e;

	e.save_out = dup(1);
	e.save_in = dup(0);
	if (ft_redirs(t->redirs, env->e_tab))
		e.ret = 1;
	else
	{
		if (t->op == PIPE)
			e.ret = ft_pipe(t->l, t->r, env);
		else if (t->op == AND)
			e.ret = ft_and(t->l, t->r, env);
		else if (t->op == OR)
			e.ret = ft_or(t->l, t->r, env);
		else if (t->op == CMD)
		{
			t->args = ft_expand_toktab(t->args, env->e_tab);
			e.ret = ft_exec_command(t->args, env);
		}
	}
	if (dup2(e.save_in, 0) < 0)
		return (1);
	if (dup2(e.save_out, 1) < 0)
		return (1);
	return (ft_finish_exec(&e));
}
