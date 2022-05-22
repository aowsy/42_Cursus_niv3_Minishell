/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:13:28 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/03 15:21:59 by mdelforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>

# define E_NOT_BUILT_IN 256

typedef struct s_env
{
	int		size;
	int		e_last;
	char	**e_tab;
}	t_env;

/*					builtins.c					*/
int		ft_dispatcher(char *cmd, char **args, t_env *env);
int		ft_error_built(char *msg, int ret, int err);

/*					built_cd.c					*/
int		ft_my_cd(char **args, t_env *env);
int		ft_my_pwd(void);

/*					built_echo.c				*/
int		ft_my_echo(char **args);

/*					built_export.c				*/
int		ft_my_export(char **args, t_env *env);

/*				built_export_utils.c			*/
int		ft_env_sorted(char **env);
int		ft_check_var(char *str);

/*					built_unset.c				*/
int		ft_my_env(char **args, t_env *env);
int		ft_my_unset(char **args, t_env *env);
int		ft_var_index(char *str, char **e_tab, int fct);

/*					built_exit.c				*/
int		ft_my_exit(char **args, t_env *env);

/*					environnement.c				*/
void	ft_create_env(t_env *env, char **envp);
void	ft_bigger_env(t_env *env, char **past_e);

/*					error_free.c				*/
int		ft_free_tab(char **tab, size_t i);
void	ft_error_exit(char *msg, t_env *env);
int		ft_error_built(char *msg, int ret, int err);

#endif
