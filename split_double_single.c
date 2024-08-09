/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_double_single.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:01:06 by jmayou            #+#    #+#             */
/*   Updated: 2024/08/09 16:06:57 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Libft/libft.h"

int ft_close(char *str, char c,int n, int start) 
{    
    int i ;
    int espace = 0;
    i = start + 1;
    if(n == 1)
    {
    while (str[i] && str[i] != c)
        i++;
    if (str[i] == c)
        return (i + 1);
    }
    else if(n == 0)
    {
    while (str[i] && str[i] != c)
        i++;
    if (str[i] == c )
        return (i);
    else if(str[i] == '\0')
        return(i);
    }
    return (-1);
}

int ft_check(char *str)
{
    int i;
    int k;
    int xhal;
    
    i = 0;
    k = 0;
    xhal = 0;
    while(str[i] != '\'' && str[i] != '\"' && str[i])
        i++;
    if(str[i] == '\0')
        return(0);
    else
    {
        if(i != 0)      
          xhal++;
        while(str[i])
        {
            if(str[i] == '\'')
                k = ft_close(str,'\'',1,i);
            else if(str[i] == '\"')
                k = ft_close(str,'\"',1,i);
            else if(str[i] != '\'' && str[i] != '\"')
            {
              if(ft_close(str,'\'',0,i) <= ft_close(str,'\"',0,i))
                  k = ft_close(str,'\'',0,i);
              else
                  k = ft_close(str,'\"',0,i);
            }
            if(k != -1)
                xhal++;
            else
                return(-1);
            i = k ;
        }
    }
    return(xhal);
}

int is_quote(char c) 
{
    if (c == '\'' || c == '\"') 
        return 1;
    return 0;
}
void    ft_filling(char *s,char **s1,int lenf,int start)
{
    int i;
    
    i = 0;
    while (i < lenf)
    {
        if(s[start] == '|' || s[start] == '<'  || s[start] == '>')
        {
            (*s1)[i++] = ' ';
            (*s1)[i++] = s[start++];
            if(s[start] == '<' || s[start] == '>')
                (*s1)[i++] = s[start++];
            (*s1)[i] = ' ';
        }
        else
            (*s1)[i] = s[start++];
        i++;
    }
    (*s1)[i] = '\0';
}
char    *ft_substr_add_space(char *s, int start, int len)
{
    char    *s1;
    int i;
    int lenf;
    i = 0;
    if (start > ft_strlen(s))
        return (ft_calloc(1, 1));
    if ((start + len) > ft_strlen(s))
        len = ft_strlen(s) - start;
    lenf = len;
    while (i < len)
    {
        if(s[start + i] == '|' || (s[start + i] == '<' && s[start + i + 1] != '<' ) || (s[start + i] == '>' && s[start + i + 1] != '>' ))
            lenf += 2;
        i++;
    }
    s1 = malloc((lenf + 1) * sizeof(char));
    ft_filling(s,&s1,lenf,start);
    return (s1);
}

void ft_split_quote(char *str, char ***command) 
{
    int count = 0;
    int in_quote = 0;
    int start = 0;
    char quote_char = '\0';
    int i = 0;

    while (str[i] != '\0') 
    {
        if (is_quote(str[i])) 
        {
            if (in_quote == 1 && str[i] == quote_char) 
            {
                in_quote = 0;
                (*command)[count++] = ft_substr(str ,start , i - start + 1);
                start = i + 1;
            } 
            else if (!in_quote) 
            {
                if (i > start) 
                    (*command)[count++] = ft_substr_add_space(str ,start, i - start);
                in_quote = 1;
                quote_char = str[i];
                start = i;
            }
        }
        i++;
    }
    if (i > start)
        (*command)[count++] = ft_substr_add_space(str , start, i - start);
    (*command)[count] = NULL;
}

char **ft_split_command(char *str)
{
    char **command;
    int len = ft_check(str);
    if (len == -1)
    {
        printf("Error: Unmatched quotes\n");
        return NULL;
    }
    else if (len == 0)
    {
        command = malloc(sizeof(char *) * 2);
        command[0] = ft_substr_add_space(str , 0, ft_strlen(str));
        command[1] = NULL;
    }
    else
    {
        command = malloc(sizeof(char *) * (len + 1));
        ft_split_quote(str,&command);
    }
    return command;
}

void printer(char **a)
{
    int i;

    i = 0;
    while (a[i])
        printf ("--%s--\n", a[i++]);    
}

int main(int ac,char **av,char **env) 
{
    // char *str = "g|h<\"<'j\">k<\"l\">>bl";
    // int i = 0;
    // char **resu = ft_split_command(str);
    
    // while(resu[i])
    // {
    //     printf("--%s--\n",resu[i]);
    //     i++;
    // }
    char **command;
    char *input;
    while(1)
    {
        input = readline("\033[0;35mminishell$ \033[0m");
        if(input == NULL)
            break;
        command = ft_split_command(input);
        printer(command);
        //printf("%s\n",input);
        // list = parsing(input);
        // excution (list);
        // free (list);
        add_history(input);
        free (input);
    }
}
