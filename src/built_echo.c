/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 17:18:38 by mdelforg          #+#    #+#             */
/*   Updated: 2022/04/23 17:20:30 by mdelforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	ft_flag_n(char *str)
{
	int	i;

	if (str[0] != '-')
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_my_echo(char **args)
{
	int	i;
	int	n_option;

	i = -1;
	n_option = 0;
	while (args[++i] && !ft_flag_n(args[i]))
		n_option++;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[++i])
			printf(" ");
	}
	if (!n_option)
		printf("\n");
	return (0);
}
