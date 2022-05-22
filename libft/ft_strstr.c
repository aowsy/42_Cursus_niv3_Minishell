/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeuneje <sjeuneje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:58:34 by sjeuneje          #+#    #+#             */
/*   Updated: 2022/05/03 16:58:35 by sjeuneje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i] && haystack[i] != needle[j])
			i++;
		while ((haystack[i + j] == needle[j]) && (j < ft_strlen(&needle[0])))
		{
			if (j == ft_strlen(&needle[0]) - 1)
				return ((char *)&haystack[i]);
			j++;
		}
		if (haystack[i])
			i++;
		else
			return (NULL);
	}
	return (NULL);
}
