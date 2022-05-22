/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:18:56 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:18:56 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "get_token.h"

typedef struct s_tree
{
	t_op			op;
	char			**args;
	t_redir			**redirs;
	struct s_tree	*l;
	struct s_tree	*r;
}	t_tree;

t_tree	*ft_node(t_op op, t_tree *l, t_tree *r);
void	ft_free_tree(t_tree *t);

// errno-like mechanism
int		ft_parse_errors(int errcode, int peek);

// parse a line into a syntactic tree ready for execution
t_tree	*ft_tree_of_line(char *line);

#endif
