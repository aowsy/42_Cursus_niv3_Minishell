/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:13:11 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:13:11 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "dyna_mem.h"
#include "star_expand.h"
#include "atoms.h"

void	ft_free_atoms(t_atom *atoms)
{
	t_atom	*save_atoms;

	save_atoms = atoms;
	if (!atoms)
		return ;
	while (atoms->type != AT_END)
	{
		if (atoms->type == AT_WORD)
			free(atoms->word);
		++atoms;
	}
	free(save_atoms);
}

void	ft_append_catted(t_dyna *tokens, t_atom *words)
{
	t_dyna	tok;
	char	*catted;

	if (words->type == AT_END)
		return ;
	ft_init_dyna(&tok);
	while (words && words->type == AT_WORD)
	{
		ft_dyna_append(&tok, words->word, ft_strlen(words->word));
		++words;
	}
	ft_dyna_zeros(&tok, 1);
	catted = (char *) ft_dedyna(&tok);
	ft_dyna_append(tokens, &catted, sizeof(char *));
}

char	**ft_fuse_atoms(t_atom *atoms)
{
	int		has_star;
	t_dyna	tokens;
	t_atom	*start;

	ft_init_dyna(&tokens);
	while (atoms->type != AT_END)
	{
		has_star = 0;
		while (atoms->type == AT_SEP)
			++atoms;
		start = atoms;
		while (atoms->type != AT_SEP && atoms->type != AT_END)
		{
			if ((atoms++)->type == AT_STAR)
				has_star = 1;
		}
		if (has_star)
			ft_starexpand(&tokens, start);
		else
			ft_append_catted(&tokens, start);
	}
	ft_dyna_zeros(&tokens, sizeof(char *));
	return ((char **) ft_dedyna(&tokens));
}
