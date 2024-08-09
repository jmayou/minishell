/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:18:57 by jmayou            #+#    #+#             */
/*   Updated: 2023/12/09 13:14:29 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		return (1);
	else
		return (0);
}

//#include <stdio.h>
// int main() {
//    char c = 'A';
//
//    if (ft_isalpha(c)) {
//        printf("%c is an alphabet character.\n", c);
//    } else {
//        printf("%c is not an alphabet character.\n", c);
//    }
//
//    return (0);
//}
