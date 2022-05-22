/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:14:14 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/17 15:27:26 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include "built_ins.h"
#include "tree.h"
#include "resource_management.h"
#include "heredoc.h"
#include "exit.h"

int	ft_free_tab(char **tab, size_t i)
{
	i++;
	while (i)
	{
		i--;
		free(tab[i]);
	}
	free(tab);
	return (0);
}

void	ft_exit(int exit_code, t_env *env)
{
	t_tree	*tree;

	tree = ft_store_tree(NULL);
	ft_free_tree(tree);
	ft_hdoc_closeall();
	ft_free_tab(env->e_tab, env->e_last);
	clear_history();
	exit((unsigned char) exit_code);
}

void	ft_error_exit(char *msg, t_env *env)
{
	if (msg)
		perror(msg);
	ft_exit(1, env);
}

int	ft_error_built(char *msg, int ret, int err)
{
	if (err)
		errno = err;
	perror(msg);
	return (ret);
}
