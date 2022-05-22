/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:27:09 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/17 17:31:50 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "heredoc.h"
#include "exec.h"
#include "tree.h"
#include "built_ins.h"
#include "resource_management.h"
#include "libft.h"
#include "var_utils.h"
#include "signals.h"
#include "utils.h"

void	ft_increment_shlvl(t_env *env)
{
	char	*export_arg[2];
	char	*tmp;
	char	*new_shlvl;

	tmp = ft_varvalue("SHLVL", env->e_tab);
	new_shlvl = ft_itoa((ft_atoi(tmp)) + 1);
	free(tmp);
	export_arg[0] = ft_strjoin("SHLVL=", new_shlvl);
	export_arg[1] = NULL;
	free(new_shlvl);
	ft_my_export(export_arg, env);
	free(export_arg[0]);
}

void	ft_term(char *line, t_tree *t, t_env *env)
{
	add_history(line);
	t = ft_tree_of_line(line);
	if (t)
	{
		ft_store_tree(t);
		ft_hdoc_readall();
		ft_exec_sigwrap(t, env);
		ft_free_tree(t);
		ft_store_tree(NULL);
	}
	else
	{
		g_exit_code = 2;
		ft_putstr_fd("Error: bad syntax\n", 2);
	}
	free(line);
	ft_hdoc_closeall();
	return ;
}

int	ft_only_whitespace(char *line)
{
	line = ft_skip_whitespace(line);
	return (!(*line));
}

int	main(int ac, char **av, char **envp)
{
	t_tree	*t;
	t_env	env;
	char	*line;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	ft_term_unctrl();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_shell_cancel);
	ft_create_env(&env, envp);
	ft_increment_shlvl(&env);
	line = readline("minishell-1.1$ ");
	t = NULL;
	while (line)
	{
		if (line && *line && !ft_only_whitespace(line))
			ft_term(line, t, &env);
		else
			free(line);
		line = readline("minishell-1.1$ ");
	}
	ft_free_tab(env.e_tab, env.e_last);
	clear_history();
	return (g_exit_code);
}
