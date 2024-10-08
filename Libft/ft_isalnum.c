/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:15:51 by jmayou            #+#    #+#             */
/*   Updated: 2024/08/10 16:04:18 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(char c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || (c <= '9'
			&& c >= '0') || (c == '_'))
		return (1);
	else
		return (0);
}

//#include <stdio.h>
// int main()
//{
//    char c = 'A';
//
//	if (ft_isalnum(c))
//	{
//        printf("%c yes\n", alphaNumChar);
//    } else {
//        printf("%c no \n", alphaNumChar);
//    }
//}
