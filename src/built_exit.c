/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 17:20:09 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/17 17:45:29 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "exit.h"
#include "resource_management.h"
#include "utils.h"

unsigned long long	atoi_bis(const char *str, int neg, int *notnum)
{
	size_t				i;
	unsigned long long	temp;

	i = 0;
	temp = 0;
	while (ft_isdigit(str[i]))
	{
		temp *= 10;
		temp += str[i] - '0';
		i++;
		if (temp > LLONG_MAX && neg < 0)
			return (0);
		else if (temp > LLONG_MAX && neg > 0)
			return (-1);
	}
	str = ft_skip_whitespace((char *) str + i);
	if (*str)
		*notnum = 1;
	return (temp);
}

int	ft_atoi_exit(const char *str, int *notnum)
{
	size_t		i;
	int			neg;
	long long	ret;

	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	neg = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	if (str[i] < '0' && str[i] > '9')
		return (0);
	ret = atoi_bis(&str[i], neg, notnum) * neg;
	return (ret);
}

int	ft_my_exit(char **args, t_env *env)
{
	long long	nb;
	int			notnum;

	notnum = 0;
	if (!args || !*args)
	{
		printf("exit\n");
		ft_exit(g_exit_code, env);
	}
	nb = ft_atoi_exit(args[0], &notnum);
	if (notnum)
	{
		ft_error_built("exit", 1, 22);
		printf("exit\n");
		ft_exit(255, env);
	}
	else if (args[0] && !args[1])
	{
		printf("exit\n");
		ft_exit((unsigned char) nb, env);
	}
	return (ft_error_built("exit", 1, 7));
}
