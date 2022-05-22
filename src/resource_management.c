/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:14:18 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:14:18 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

int	g_exit_code = 0;

t_tree	*ft_store_tree(t_tree *tree)
{
	static t_tree	*last_tree;
	t_tree			*ret;

	ret = last_tree;
	last_tree = tree;
	return (ret);
}
