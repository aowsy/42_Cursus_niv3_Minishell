/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:18:28 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:18:28 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H

# include "atoms.h" 

typedef struct s_builder
{
	size_t	i;
	char	*active_str;
	char	*str_after;
	char	**env;
	t_dyna	atoms;
}	t_builder;

// option flags for 'ft_launch_builder'
# define BUILDER_INIT 1
# define BUILDER_FINISH 2

// t is a builder that object that will, when `options & BUILDER_FINISH`, will 
// will be destroyed to return a null-terminated list of atoms
// 
// Returns NULL unless BUILDER_FINESH option is used.
// BUILDER_INIT must be used to init the builder obj the first time.
// Use BUILDER_FINISH when you are done with it and want the atom array.
//
// This will do things like :
// 	erase quotes
// 	expand variables 
// 	put AT_SEP-type words where there is unescaped whitespace etc
//
t_atom	*ft_launch_builder(t_builder *t, char *str, char **env, int options);

#endif
