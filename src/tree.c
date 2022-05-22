/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:14:21 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:14:21 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "tree.h"

void	ft_free_tree(t_tree *t)
{
	size_t	i;

	if (!t)
		return ;
	ft_free_strtab(t->args);
	i = 0;
	while (t->redirs && t->redirs[i])
		ft_free_redir(t->redirs[i++]);
	free(t->redirs);
	ft_free_tree(t->l);
	ft_free_tree(t->r);
	free(t);
}

t_tree	*ft_node(t_op op, t_tree *l, t_tree *r)
{
	t_tree	*t;

	t = malloc(sizeof(t_tree));
	if (!t)
		return (NULL);
	t->redirs = NULL;
	t->args = NULL;
	t->op = op;
	t->l = l;
	t->r = r;
	return (t);
}

int	ft_parse_errors(int errcode, int peek)
{
	static int	last_errcode = 0;
	int			ret;

	if (peek)
		return (last_errcode);
	ret = last_errcode;
	last_errcode = errcode;
	return (ret);
}
