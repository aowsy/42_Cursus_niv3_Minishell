/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:18:19 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:18:22 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOMS_H
# define ATOMS_H

# include "dyna_mem.h"

typedef enum s_atom_type {AT_WORD, AT_SEP, AT_STAR, AT_END}	t_atom_type;

// a piece of string or special indicator 
// to be recombined (eventually) as a string representing 
// a token to be understood as *one* argument 
// (or program name etc) by execve & co.
// 	type: separator, word etc (t_atom_type)
// 	word: ignored except if type = AT_WORD
typedef struct s_atom {
	t_atom_type	type;
	char		*word;
}	t_atom;

// here : t_dyna "type" ~= char **
// concatenate the words first consecutive sequence of atoms of type AT_WORD
// append it to the unfinshed list of string represented by 'tokens'
void	ft_append_catted(t_dyna *tokens, t_atom *words);

// free an array of atoms and its contents
void	ft_free_atoms(t_atom *atoms);

// recombine an array of atoms into a null-terminated array of strings
// note : the number of strings and atoms is *rarely* the same
char	**ft_fuse_atoms(t_atom *atoms);

#endif
