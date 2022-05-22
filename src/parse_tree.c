/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:14:17 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/17 17:45:28 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tree.h"
#include "get_token.h"
#include "dyna_mem.h"
#include "utils.h"

static t_tree	*ft_parse_cmd(char **line, t_tok *tok)
{
	t_tree	*t;
	t_dyna	args;
	t_dyna	redirs;

	ft_init_dyna(&args);
	ft_init_dyna(&redirs);
	t = ft_node(CMD, NULL, NULL);
	while (tok)
	{
		if (tok->type == STR)
			ft_dyna_append(&args, &(tok->data.str), sizeof(char *));
		else if (tok->type == REDIR)
			ft_dyna_append(&redirs, &(tok->data.redir), sizeof(t_redir *));
		else
			break ;
		tok = ft_consume_token(line, tok);
	}
	ft_dyna_zeros(&args, sizeof(char *));
	t->args = (char **) ft_dedyna(&args);
	ft_dyna_zeros(&redirs, sizeof(char *));
	t->redirs = (t_redir **) ft_dedyna(&redirs);
	return (t);
}

static t_tree	*ft_recaux(char **line, int min_prio, t_tok *tok);
static t_tree	*ft_parse_lhs(char **line, t_tok *tok);

static t_tree	*ft_add_redirs(t_tree *t, char **line, t_tok *tok)
{
	t_dyna	redirs;
	size_t	n;

	ft_consume_token(line, tok);
	if (tok->type != REDIR)
		return (t);
	ft_init_dyna(&redirs);
	if (t->redirs != NULL)
	{
		n = 0;
		while (t->redirs[n])
			++n;
		ft_dyna_append(&redirs, t->redirs, sizeof(t_redir *) * n);
		free(t->redirs);
	}
	while (tok->type == REDIR)
	{
		ft_dyna_append(&redirs, &(tok->data.redir), sizeof(t_redir *));
		ft_consume_token(line, tok);
	}
	ft_dyna_zeros(&redirs, sizeof(t_redir *));
	t->redirs = (t_redir **) ft_dedyna(&redirs);
	return (t);
}

static t_tree	*ft_parse_lhs(char **line, t_tok *tok)
{
	t_tree	*left;

	ft_consume_token(line, tok);
	ft_parse_errors(1, 0);
	if (tok->type == OP && tok->data.op == OPAREN)
	{
		left = ft_recaux(line, 0, tok);
		if (ft_parse_errors(0, 1)
			|| !(tok->type == OP && tok->data.op == CPAREN))
		{
			ft_parse_errors(1, 0);
			return (left);
		}
		ft_add_redirs(left, line, tok);
	}
	else if (tok->type == STR || tok->type == REDIR)
		left = ft_parse_cmd(line, tok);
	else
		return (NULL);
	ft_parse_errors(0, 0);
	return (left);
}

static t_tree	*ft_recaux(char **line, int min_prio, t_tok *tok)
{
	int				prio;
	t_op			tmp;
	t_tree			*lhs;

	lhs = ft_parse_lhs(line, tok);
	if (ft_parse_errors(0, 1) || !lhs)
		return (lhs);
	while (tok->type != END && !(tok->type == OP && tok->data.op == CPAREN))
	{
		ft_parse_errors(1, 0);
		if (tok->type == OP && (tok->data.op == PIPE))
			prio = 2;
		else if (tok->type == OP && (tok->data.op == AND || tok->data.op == OR))
			prio = 1;
		else
			return (lhs);
		ft_parse_errors(0, 0);
		if (prio < min_prio)
			return (lhs);
		tmp = tok->data.op;
		lhs = ft_node(tmp, lhs, ft_recaux(line, prio + 1, tok));
	}
	return (lhs);
}

t_tree	*ft_tree_of_line(char *line)
{
	t_tok	tok;
	t_tree	*t;

	ft_parse_errors(0, 0);
	t = ft_recaux(&line, 0, &tok);
	if (ft_parse_errors(0, 1) || tok.type != END)
	{
		ft_free_tree(t);
		ft_free_tok_contents(&tok);
		return (NULL);
	}
	return (t);
}
