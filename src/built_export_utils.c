/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 17:09:01 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/17 15:31:05 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	ft_check_var(char *str)
{
	int	i;

	if (!str[0] || str[0] == '=' || ft_isdigit((int)str[0]))
		return (ft_error_built("export", 1, 22));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '='
			&& str[i] != '_' && !(str[i] == '+' && str[i + 1] == '='))
			return (ft_error_built("export", 1, 22));
		i++;
	}
	return (0);
}

int	*ft_env_index(char **env, int a)
{
	int	max;
	int	i;
	int	*index;

	max = 0;
	while (env[max])
		max++;
	index = (int *)malloc(sizeof(int) * (max + 1));
	if (!index)
		exit(-1);
	while (a < max)
	{
		index[a] = 0;
		i = 0;
		while (env[i])
		{
			if (ft_strncmp(env[a], env[i], ft_strlen(env[a])) > 0)
				index[a]++;
			i++;
		}
		a++;
	}
	index[a] = -1;
	return (index);
}

void	ft_putstr_export(char *str)
{
	int	i;

	printf("declare -x ");
	i = 0;
	while (str[i] && str[i - 1] != '=')
	{
		printf("%c", str[i]);
		i++;
	}
	if (str[i - 1] == '=')
	{
		printf("\"");
		while (str[i])
		{
			printf("%c", str[i]);
			i++;
		}
		printf("\"");
	}
	printf("\n");
	return ;
}

int	ft_env_sorted(char **env)
{
	int	i;
	int	nb;
	int	max;
	int	*index;

	index = ft_env_index(env, 0);
	max = 0;
	while (env[max])
		max++;
	nb = 0;
	while (nb < max)
	{
		i = 0;
		while (env[i])
		{
			if ((index[i] == nb) && !(env[i][0] == '_' && env[i][1] == '='))
				ft_putstr_export(env[i]);
			i++;
		}
		nb++;
	}
	free(index);
	return (0);
}
