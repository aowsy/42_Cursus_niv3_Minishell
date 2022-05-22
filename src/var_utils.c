/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:14:22 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:14:22 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "var_utils.h"
#include "resource_management.h"

/* find (and alloc) the value of variable 'key' where env is 
 * a null-terminated array of "var=value" strings */
char	*ft_varvalue(char const *key, char **env)
{
	size_t	keysz;
	char	*empty;

	if (!ft_strncmp(key, "?", 2))
		return (ft_itoa(g_exit_code));
	keysz = ft_strlen(key);
	while (*env)
	{
		if (ft_strncmp(key, *env, keysz) == 0 && (*env)[keysz] == '=')
			return (ft_strdup(*env + keysz + 1));
		++env;
	}
	empty = malloc(1);
	if (empty)
		*empty = '\0';
	return (empty);
}

/* is '_' or an alnum character
 * these are the characters allowed in bash variable names */
static int	ft_isvarchar(char c)
{
	return (c == '_' || ft_isalpha(c) || ft_isdigit(c));
}

/* returns the longest uninterrupted substring 
 * containing only '_' or alnum characters
 * at the start of 'start' 
 * 
 * The idea is that, if for example :
 * s = "123$varname whatever"
 * then ft_parse_name(s + 4) is the name of the 
 * variable that must be expanded, ie "varname" */
char	*ft_parse_varname(char const *start)
{
	size_t	sz;

	sz = 0;
	if (*start == '?')
		sz = 1;
	else
	{
		while (ft_isvarchar(start[sz]))
			++sz;
	}
	return (ft_substr(start, 0, sz));
}

char	*ft_skip_var(char **str, char **env)
{
	char	*varname;
	char	*varval;

	varval = NULL;
	varname = ft_parse_varname(*str);
	if (*varname)
	{
		varval = ft_varvalue(varname, env);
		*str += ft_strlen(varname);
	}
	free(varname);
	return (varval);
}
