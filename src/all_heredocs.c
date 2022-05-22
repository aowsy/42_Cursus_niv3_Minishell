/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:12:52 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:12:55 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "heredoc.h"

// access the list of current heredocs :
// (as described in 2nd paragraph)
// they can be in 2 states -being built, 
// and thus represented by a t_dyna types- 
// or "finished" and represnted by a malloced array.
//
// if dy is not null : make it point to the t_dyna struct
// *then* if hdocs is not null :
//   if a t_dyna is being built 
//     transforms it into an array and make hdocs point to it
//   else make hdocs point to the last such array that was transformed
//
// if both dy and hdocs are null, set the list of current heredocs to NULL
static void	ft_get_hdocs(t_dyna **dy, t_hdoc ***hdocs)
{
	static t_dyna	st_dy;
	static t_hdoc	**st_hdocs = NULL;
	static int		init = 0;

	if (!dy && !hdocs)
		st_hdocs = NULL;
	if (!init && dy)
	{
		ft_init_dyna(&st_dy);
		init = 1;
	}
	if (dy)
		*dy = &st_dy;
	if (hdocs)
	{
		if (init)
		{
			ft_dyna_zeros(&st_dy, sizeof(t_hdoc *));
			st_hdocs = ft_dedyna(&st_dy);
			init = 0;
		}
		*hdocs = st_hdocs;
	}
}

// close all current heredocs and free their ressources
//
// note : careful not to close twice
void	ft_hdoc_closeall(void)
{
	t_hdoc	**hdocs;
	size_t	i;

	ft_get_hdocs(NULL, &hdocs);
	i = 0;
	while (hdocs && hdocs[i])
	{
		close(hdocs[i]->pipefd[0]);
		close(hdocs[i]->pipefd[1]);
		free(hdocs[i]->name);
		free(hdocs[i]);
		++i;
	}
	free(hdocs);
	ft_get_hdocs(NULL, NULL);
}

// add an heredoc
// name is a bash-style token that can contain quotes that will not appear 
// in the final heredoc name (unless escaped by other quotes, etc)
// 
// return the the fd of the read-end (out) of the pipe (or -1 if error)
int	ft_add_hdoc(char *name)
{
	t_hdoc	*newdoc;
	t_dyna	*hdocs;

	newdoc = malloc(sizeof(t_hdoc));
	if (!newdoc)
		return (-1);
	newdoc->name = ft_dequote(name);
	ft_get_hdocs(&hdocs, NULL);
	hdocs = ft_dyna_append(hdocs, &newdoc, sizeof(t_hdoc *));
	if (!hdocs || !(newdoc->name) || pipe(newdoc->pipefd) == -1)
	{
		free(newdoc);
		return (-1);
	}
	return (newdoc->pipefd[0]);
}

// read stdin until all current hdocs are filled
// (ie they were closed by a single line containing their name)
void	ft_hdoc_readall(void)
{
	t_hdoc	**hdocs;

	ft_get_hdocs(NULL, &hdocs);
	if (!hdocs)
		return ;
	while (*hdocs)
	{
		ft_read_hdoc(*(hdocs++));
	}
}
