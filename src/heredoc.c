/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:14:16 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:14:16 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "heredoc.h"

// fill heredoc with contents from stdin until
// a the line "<hdoc->name>" is encountered
void	ft_read_hdoc(t_hdoc *hdoc)
{
	char	*line;

	line = readline("> ");
	while (ft_strncmp(line, hdoc->name, ft_strlen(line) + 1))
	{
		write(hdoc->pipefd[1], line, ft_strlen(line));
		write(hdoc->pipefd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(hdoc->pipefd[1]);
	hdoc->pipefd[1] = -1;
}

static void	ft_dequote_helper(char *token, t_dyna *dy)
{
	char	quote;
	size_t	i;

	quote = 0;
	i = 0;
	while (token[i])
	{
		if ((!quote && (token[i] == '\'' || token[i] == '"'))
			|| token[i] == quote)
		{
			quote = token[i];
			ft_dyna_append(dy, token, i++);
			token += i;
			i = 0;
		}
		else
			++i;
	}
	ft_dyna_append(dy, token, i);
}

// Remove quotes from a token (bash rules)
// Meant for heredoc names
// eg :	
// 	"foo" -> foo
// 	"'foo'b"'ar"q'ux -> 'foo'bar"qux
//
// 'token' will be freed and replaced with the new string
char	*ft_dequote(char *token)
{
	t_dyna	dy;
	char	*save_token;

	ft_init_dyna(&dy);
	save_token = token;
	ft_dequote_helper(token, &dy);
	ft_dyna_zeros(&dy, 1);
	free(save_token);
	return (ft_dedyna(&dy));
}
