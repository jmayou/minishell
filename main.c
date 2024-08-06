/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:58:50 by jmayou            #+#    #+#             */
/*   Updated: 2024/08/06 16:52:08 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>

int main()
{
    char *input;
    while(1)
    {
        input = readline("minishell$ ");
        //printf("%s\n",input);
        // list = parsing(input);
        // excution (list);
        // free (list);
        add_history(input);
        free (input);
    }
}