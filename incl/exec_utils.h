/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:40:41 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/04/27 15:41:55 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_path
{
	char	*path;
	char	*env_paths;
	char	**paths;
	char	*tmp;
	int		i;
}	t_path;

char	*ft_get_path(char *command, char **env);
int		ft_get_size(t_redir **redirs);
int		ft_containschar(char *str, char c);

#endif
