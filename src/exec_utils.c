/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:20:53 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/04/27 17:22:23 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "exec_utils.h"
#include "libft.h"
#include "var_utils.h"
#include "exec3.h"

int	ft_get_size(t_redir **redirs)
{
	int	size;

	size = 0;
	while (redirs[size])
		size++;
	return (size);
}

int	ft_containschar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_free_paths(char **paths, char *path, int mode)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	if (mode)
		return (path);
	else
		return (NULL);
}

int	ft_is_executable(char *path)
{
	struct stat	m;

	lstat(path, &m);
	return (access(path, X_OK) != -1 && !(S_ISDIR(m.st_mode)));
}

char	*ft_get_path(char *command, char **env)
{
	t_path	p;

	p.i = 0;
	if (ft_containschar(command, '/'))
		return (ft_strdup(command));
	p.env_paths = ft_varvalue("PATH", env);
	if (!p.env_paths)
		return (NULL);
	p.paths = ft_split(p.env_paths, ':');
	free(p.env_paths);
	if (!p.paths)
		return (NULL);
	while (p.paths[p.i])
	{
		p.tmp = ft_strjoin(p.paths[p.i], "/");
		p.path = ft_strjoin(p.tmp, command);
		free(p.tmp);
		if (ft_is_executable(p.path))
			return (ft_free_paths(p.paths, p.path, 1));
		free(p.path);
		p.i++;
	}
	return (ft_free_paths(p.paths, p.path, 0));
}
