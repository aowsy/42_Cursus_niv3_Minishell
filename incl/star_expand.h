/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expand.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:18:52 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:18:52 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STAR_EXPAND_H
# define STAR_EXPAND_H

# include "atoms.h"

// true or false:
// str is compatible with the parttern 'pat'
// where 'pat' represents a bash-like wildcard expansion pattern
// ( see atoms.h for the actual representation of pat)
// eg : str			pat			res
// 		'hello', 	{*, 'lo'} 	-> true
// 		'hello', 	{*, 'll'}	-> false
// 		'hello', 	{*, 'a', *} -> false
int		ft_matches_glob(char *str, t_atom *pat);

// for all filenames in the current directory
// if it matches the pattern add it to the unfinshed list 'tokens'
// else ignore it
void	ft_starexpand(t_dyna *tokens, t_atom *pat);

#endif
