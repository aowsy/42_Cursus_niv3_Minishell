/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:48:59 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/03 14:14:54 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	ft_my_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (ft_error_built("pwd", 1, 0));
	else
		printf("%s\n", path);
	return (0);
}

char	*ft_find_inenv(char *var, t_env *env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env->e_tab[i] && !ft_strstr(env->e_tab[i], var))
		i++;
	if (!env->e_tab[i])
		return (NULL);
	j = 0;
	while (env->e_tab[i][j] && env->e_tab[i][j] != '/')
		j++;
	str = &env->e_tab[i][j];
	return (str);
}

int	ft_my_cd(char **args, t_env *env)
{
	int	ret;

	ret = 0;
	if (!args || !*args)
		ret = chdir(ft_find_inenv("HOME", env));
	else if (*(args[0]))
		ret = chdir(args[0]);
	if (ret < 0)
		return (ft_error_built("cd", 1, 0));
	return (0);
}
