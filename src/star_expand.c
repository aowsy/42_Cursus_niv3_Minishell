/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:14:19 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/17 17:23:33 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "dyna_mem.h"
#include "atoms.h"
#include "star_expand.h"

static char	*ft_cat_wordseq(t_atom **atoms_addr)
{
	t_dyna	dy;
	t_atom	*atoms;

	atoms = *atoms_addr;
	ft_init_dyna(&dy);
	while (atoms->type == AT_WORD)
	{
		ft_dyna_append(&dy, atoms->word, ft_strlen(atoms->word));
		++atoms;
	}
	ft_dyna_zeros(&dy, 1);
	*atoms_addr = atoms;
	return (ft_dedyna(&dy));
}

static int	ft_matches_star_etc(char *str, t_atom *pat)
{
	char	*concat;
	int		ret;

	ret = 0;
	while (pat->type == AT_STAR)
		++pat;
	if (pat->type == AT_SEP)
		return (1);
	if (pat->type == AT_WORD)
	{
		concat = ft_cat_wordseq(&pat);
		str = ft_strstr(str, concat);
		if (!str)
			ret = 0;
		else if (pat->type == AT_SEP)
		{
			str = str + ft_strlen(str) - ft_strlen(concat);
			ret = !ft_strncmp(str, concat, ft_strlen(concat));
		}
		else if (pat->type == AT_STAR)
			ret = ft_matches_star_etc(str + ft_strlen(concat), pat);
		free (concat);
		return (ret);
	}
	return (0);
}

int	ft_matches_glob(char *str, t_atom *pat)
{
	int	len_start;

	len_start = 0;
	while (pat->type == AT_WORD)
	{
		if (!ft_strncmp(str, pat->word, ft_strlen(pat->word)))
		{
			len_start += ft_strlen(pat->word);
			str += len_start;
			++pat;
		}
		else
			return (0);
	}
	if (pat->type == AT_STAR)
	{
		if (*str == '.' && !len_start)
			return (0);
		return (ft_matches_star_etc(str, pat));
	}
	else
		return (!(*str));
}

void	ft_starexpand(t_dyna *tokens, t_atom *pat)
{
	DIR				*dir;
	char			*cwd;
	struct dirent	*file;
	char			*dup;

	cwd = getcwd(NULL, 0);
	dir = opendir(cwd);
	free(cwd);
	file = readdir(dir);
	while (file)
	{
		if (ft_matches_glob(file->d_name, pat))
		{
			dup = ft_strdup(file->d_name);
			ft_dyna_append(tokens, &dup, sizeof(char *));
		}
		file = readdir(dir);
	}
	closedir(dir);
}
