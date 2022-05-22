/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varstar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:14:23 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:14:23 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builder.h"
#include "atoms.h"
#include "utils.h"

char	**ft_expand_toktab(char **oldtokens, char **env)
{
	t_builder	builder;
	t_atom		*atoms;
	char		**new_tokens;
	size_t		i;

	ft_launch_builder(&builder, NULL, env, BUILDER_INIT);
	i = 0;
	while (oldtokens[i])
		ft_launch_builder(&builder, oldtokens[i++], env, 0);
	atoms = ft_launch_builder(&builder, NULL, env, BUILDER_FINISH);
	ft_free_strtab(oldtokens);
	new_tokens = ft_fuse_atoms(atoms);
	ft_free_atoms(atoms);
	return (new_tokens);
}

char	*ft_redir_expand(char *fn, char **env)
{
	t_builder	build;
	t_atom		*atoms;
	char		**new_tokens;
	char		*true_filename;

	atoms = ft_launch_builder(&build, fn, env, BUILDER_INIT | BUILDER_FINISH);
	new_tokens = ft_fuse_atoms(atoms);
	ft_free_atoms(atoms);
	if (!new_tokens[0] || new_tokens[1])
	{
		ft_free_strtab(new_tokens);
		return (NULL);
	}
	true_filename = ft_strdup(new_tokens[0]);
	ft_free_strtab(new_tokens);
	return (true_filename);
}
