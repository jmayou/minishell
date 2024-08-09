/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:32:23 by jmayou            #+#    #+#             */
/*   Updated: 2023/12/31 19:40:08 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst == 0 && src == 0)
		return (NULL);
	else if (dst > src)
	{
		while (len != 0)
		{
			len--;
			((char *)dst)[len] = ((char *)src)[len];
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}

//#include <stdio.h>
//#include <string.h>
//
// int main()
//{
//    char str1[] = "Hello, World!";
//    printf(" %s\n", ft_memmove(str1 , str1 + 8 ,4));
//	return (0);
//}
