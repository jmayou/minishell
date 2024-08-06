/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_double_single.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:01:06 by jmayou            #+#    #+#             */
/*   Updated: 2024/08/06 17:24:31 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char *ft_filling(char *str,int *start)
{
    int i = 0;
    int what = 0;
    while(str[(*start)] != '\'' && str[(*start)] != '\"' && str[(*start)])
        i++;
    if(str[(*start)] == '\'')
        what = 1;
    else
        what = 2;
    
    i++;
    
    
    
}
char **ft_split_command(char *str)
{
    char **command;
    int i;
    int len;
    int j;

    len = ft_check(str);
    i = 0;
    j = 0;
    if(len == -1)
        error();
    else if(len == 0)
        command = ft_split(str);
    else
    {
    command = malloc(sizeof(char *) * (len + 1));
    while(j < len)
    {
        command[j] = ft_filling(str,&i);
        j++;
    }
    }
}

int main() {
char *str = "He 'w' \"f bar\"test";
printf("%d\n",ft_check(str));
  return 0;
}
