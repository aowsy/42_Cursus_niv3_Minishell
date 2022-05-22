/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:16:23 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/17 16:22:28 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	ft_dispatcher(char *cmd, char **args, t_env *env)
{
	if (!ft_strncmp(cmd, "env", 4))
		return (ft_my_env(args, env));
	else if (!ft_strncmp(cmd, "export", 7))
		return (ft_my_export(args, env));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (ft_my_unset(args, env));
	else if (!ft_strncmp(cmd, "echo", 5))
		return (ft_my_echo(args));
	else if (!ft_strncmp(cmd, "cd", 3))
		return (ft_my_cd(args, env));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (ft_my_pwd());
	else if (!ft_strncmp(cmd, "exit", 5))
		return (ft_my_exit(args, env));
	return (E_NOT_BUILT_IN);
}
