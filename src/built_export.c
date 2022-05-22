/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:45:03 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/17 16:24:49 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	ft_export_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	if (str[i] == '+' && str[i + 1] == '=')
		return (i + 2);
	return (-1);
}

void	ft_not_inenv(int i, int j, char **args, t_env *env)
{
	int	plus;

	plus = ft_export_plus(args[j]);
	if (plus > 0)
	{
		env->e_tab[i] = ft_substr(args[j], 0, plus - 2);
		env->e_tab[i] = ft_strjoin(env->e_tab[i], &args[j][plus - 1]);
		env->e_last++;
	}
	else
	{
		env->e_tab[i] = ft_strdup(args[j]);
		env->e_last++;
	}
	if (!env->e_tab[i])
		ft_error_exit("malloc", env);
	return ;
}

void	ft_already_inenv(int a, int j, char **args, t_env *env)
{
	int	plus;

	plus = ft_export_plus(args[j]);
	if (plus > 0)
		env->e_tab[a] = ft_strjoin(env->e_tab[a], &args[j][plus]);
	else
	{
		free(env->e_tab[a]);
		env->e_tab[a] = ft_strdup(args[j]);
	}
	if (!env->e_tab[a])
		ft_error_exit("malloc", env);
	return ;
}

int	ft_my_export(char **args, t_env *env)
{
	int	a;
	int	j;
	int	ret;

	j = 0;
	if (!args || !*args)
		return (ft_env_sorted(env->e_tab));
	ret = 0;
	while (args[j])
	{
		if (!ft_check_var(args[j]))
		{
			a = ft_var_index(args[j], env->e_tab, 1);
			if (a >= 0)
				ft_already_inenv(a, j, args, env);
			else
				ft_not_inenv(env->e_last + 1, j, args, env);
		}
		else
			ret = 1;
		j++;
		if (env->e_last == env->size -1)
			ft_bigger_env(env, env->e_tab);
	}
	return (ret);
}
