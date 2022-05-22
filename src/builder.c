/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:13:14 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:13:14 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "var_utils.h"
#include "utils.h"
#include "atoms.h"
#include "builder.h"
#include "star_expand.h"

#define WHITESPACE " \t\n\r\f\v"

static void	ft_builder_add(t_builder *t, t_atom_type type, int skip)
{
	t_atom	new_word;

	new_word.type = type;
	new_word.word = NULL;
	if (type == AT_WORD)
	{
		new_word.word = ft_substr(t->active_str, 0, t->i);
		t->active_str += t->i;
	}
	if (skip)
		++(t->active_str);
	if (type == AT_SEP)
		t->active_str = ft_skip_whitespace(t->active_str);
	if (type == AT_STAR)
	{
		while (*(t->active_str) == '*')
			++(t->active_str);
	}
	t->i = 0;
	ft_dyna_append(&(t->atoms), &new_word, (sizeof(t_atom)));
}

static int	ft_builder_done(t_builder *t)
{
	if (t->active_str[t->i] == '\0')
	{
		ft_builder_add(t, AT_WORD, 0);
		return (1);
	}
	else
		return (0);
}

// needed for mutual recursion since prototypes not in .h
static void	ft_builder_walk(t_builder *t, char *special, char quote);

static void	ft_builder_dovar(t_builder *t, char quote)
{
	char	*varvalue;

	varvalue = ft_skip_var(&(t->active_str), t->env);
	if (!varvalue)
		varvalue = ft_strdup("$");
	t->str_after = t->active_str;
	t->active_str = varvalue;
	if (quote == 0)
		ft_builder_walk(t, WHITESPACE, 0);
	if (quote == '"')
		ft_builder_walk(t, "", 0);
	free(varvalue);
	t->active_str = t->str_after;
	t->str_after = NULL;
	return ;
}

static void	ft_builder_walk(t_builder *t, char *special, char quote)
{
	char	c;

	while (!ft_builder_done(t))
	{
		c = t->active_str[t->i];
		if (ft_is_in(special, c))
		{
			ft_builder_add(t, AT_WORD, 1);
			if (c == '*')
				ft_builder_add(t, AT_STAR, 0);
			if (c == '$')
				ft_builder_dovar(t, quote);
			if (c == quote)
				return ;
			if (c == '\'')
				ft_builder_walk(t, "'", '\'');
			if (c == '"')
				ft_builder_walk(t, "$\"", '"');
			if (ft_is_in(WHITESPACE, c))
				ft_builder_add(t, AT_SEP, 0);
		}
		else
			++(t->i);
	}
}

// in .h
// #define BUILDER_INIT 1
// #define BUILDER_FINISH 2
t_atom	*ft_launch_builder(t_builder *t, char *str, char **env, int options)
{
	t_atom	*ret;

	ret = NULL;
	if (options & BUILDER_INIT)
		ft_init_dyna(&(t->atoms));
	if (str)
	{
		t->i = 0;
		t->active_str = str;
		t->str_after = NULL;
		t->env = env;
		ft_builder_walk(t, WHITESPACE "*$\"'", 0);
		ft_builder_add(t, AT_SEP, 0);
	}
	if (options & BUILDER_FINISH)
	{
		ft_builder_add(t, AT_END, 0);
		ret = (t_atom *) ft_dedyna(&(t->atoms));
	}
	return (ret);
}

#undef WHITESPACE
