/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varstar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:20:28 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 14:20:28 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARSTAR_H
# define VARSTAR_H

char	**ft_expand_toktab(char **oldtokens, char **env);
char	*ft_redir_expand(char *filename, char **env);

#endif
