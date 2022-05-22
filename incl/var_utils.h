/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:20:26 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:20:26 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_UTILS_H
# define VAR_UTILS_H

/* find (and alloc) the value of variable 'key' where env is 
 * a null-terminated array of "var=value" strings */
char	*ft_varvalue(char const *key, char **env);

/* returns the longest uninterrupted substring 
 * containing only '_' or alnum characters
 * at the start of 'start' 
 * 
 * The idea is that, if for example :
 * s = "123$varname whatever"
 * then ft_parse_name(s + 4) is the name of the 
 * variable that must be expanded, ie "varname" */
char	*ft_parse_varname(char const *start);

/* return a string containing the result of 'line' with 
 * its variables expanded according to key-value pairings
 * in env */
char	*ft_varexpand(char const *line, char **env);

/* 'str' points to a string starting with a variable defined in 'env'.
 * return the string the is the value of the variable.
 * make 'str' point to the string just after the variable name.
 * eg :
 * 	env = {"foo=bar", ...}
 * 	str = "foo hello"
 * 	varval = ft_skip_var(&str, env); -> varval = "bar", str = " hello"
 */
char	*ft_skip_var(char **str, char **env);

#endif
