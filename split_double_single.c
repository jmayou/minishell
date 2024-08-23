/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_double_single.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:01:06 by jmayou            #+#    #+#             */
/*   Updated: 2024/08/23 18:40:26 by jmayou           ###   ########.fr       */
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
        return (1);
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
int ft_strcmp_len(char *s1,char *s2, int len)
{
    int	i;

	i = 0;
	while (i < len && s1[i] && s2[i])
	{
        if(s1[i] == s2[i])
            i++;
        else
            break;
	}
    if(i == len)
        return(0);
	return (s1[i] - s2[i]);
}

char *get_env_value(char **env, char *var)
{
    int i = 0;
    int len = ft_strlen(var);
    
    while(env[i])
    {
        if(ft_strcmp_len(env[i],var,len) == 0 && env[i][len] == '=')
            return(env[i] + len + 1);
        i++;
    }
    return(NULL);
}
char *get_variable(char *command,int pos)
{
    char *var;
    int i = 0;
    while(command[i + pos])
    {
        if(ft_isalnum(command[i + pos])== 0)
            break;
        i++;
    }
    var = ft_substr(command,pos,i);
    return(var);
}
char *ft_replace(char *command,char *var,char *value,int k)
{
    int i = 0;
    int j = 0;
    int len_val = ft_strlen(value);
    int len_var = ft_strlen(var);
    int len_all = ft_strlen(command) - len_var - 1 + len_val;
    char *resu;
    int lock = 1;

    resu = malloc(len_all + 1);
    while(command[i])
    {
        if(command[i] == '$' && lock)
        {
            k = 0;
            while(value && (k < len_val))
            {
                resu[j++] = value[k++];
            }
            i += len_var;
            lock = 0;
        }
        else
            resu[j++] = command[i];
        i++;
    }
    resu[j] = '\0';
    return(resu);
}
void  ft_search_variable(char ***command,char **env)
{
    int i = -1;
    int j = 0;
    char *var;
    char *value;
    char *tmp;
    int len;
    
    while((*command)[++i])
    {
        len = ft_strlen((*command)[i]);
        if((*command)[i][0] != '\'')
        {
            j = -1;
            while (++j < len)
            {
                if((*command)[i][j] == '$')
                {
                    var = get_variable((*command)[i], j + 1);
                    j += ft_strlen (var);
                    value = get_env_value(env, var);
                    tmp = ft_replace((*command)[i], var, value, 0);
                    free (var);
                    free((*command)[i]);
                    (*command)[i] = tmp;
                    len = ft_strlen((*command)[i]);
                }
            }
        }
    }
}
int is_space(char c) 
{
    return (c == ' ' || c == '\t');
}
char *get_last_word(char *str) 
{
    char *last_word;
    int len = ft_strlen(str);
    while (len > 0 && !is_space(str[len - 1])) {
        len--;
    }
    last_word = ft_strdup(&str[len]);
    return last_word;
}

char *get_first_word(char *str) {
    int len = 0;
    int i = 0;
    while (str[len] && !is_space(str[len])) {
        len++;
    }
    char *word = (char *)malloc(len + 1);
    while(i < len)
    {
        word[i] = str[i];
        i++;
    }
     word[i] = '\0';
    return word;
}
void    ft_strcpy(char *s1, char *s2)
{
	int i = 0;
	
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}
char *ft_remove(char *str,int len_r, int n)
{
    int i;
    int j;
    int len;
    int len_s;
    char *resu;

    len_s = ft_strlen(str);
    len = len_s - len_r + 1;
    resu = malloc(len);
    if(n == 1)
    {
        i = -1;
        while(++i < len - 1)
            resu[i] = str[i];
    }
    else if(n == 0)
    {
        i = len_s - len_r;
        j = 0;
        while(j < len - 1)
            resu[j++] = str[i++];
        i = j;
    }
    resu[i] = '\0';
    return(resu);
}
void    ft_collect_in_first(char **next,char **str)
{
    int len_next;
    int len_word;
    char *word;
    char *new_next;
    char *new_str;
    word = get_last_word((*str));
    len_word = ft_strlen(word);
    len_next = ft_strlen((*next));
    new_next = malloc(len_next + len_word + 1);
    new_next[0] = (*next)[0];
    ft_strcpy(new_next + 1, word);

    ft_strcpy(new_next + (1 + len_word), (*next) + 1);
    free((*next));
    (*next) = new_next;
    free(word);
    new_str = ft_remove((*str),len_word, 1);
    free((*str));
    (*str) = new_str;
}
void    ft_collect_in_last(char **next,char **str)
{
    int len_next;
    int len_word;
    char *word;
    char *new_next;
    char *new_str;
    word = get_first_word((*str));
    len_word = ft_strlen(word);
    len_next = ft_strlen((*next));
    new_next = malloc(len_next + len_word + 1);
    ft_strcpy(new_next ,(*next));
    ft_strcpy(new_next + (len_next - 1), word);
    new_next[len_next + len_word - 1] = (*next)[len_next - 1];
    new_next[len_next + len_word ] = '\0';
    free((*next));
    (*next) = new_next;
    free(word);
    new_str = ft_remove((*str),len_word, 0);
    free((*str));
    (*str) = new_str;
}

char **ft_join(char **str)
{
    int i = 0;
    int len;
    int k = 0;
    int len_next;
    while (str[i] && str[i + 1]) 
    {
        len = ft_strlen(str[i]);
        len_next = ft_strlen(str[i + 1]);
       if(is_space(str[i][len - 1]) == 0 && (str[i + 1][0] == '\'' || str[i + 1][0] == '\"'))
       {
            ft_collect_in_first(&str[i + 1],&str[i]); 
            if(ft_strcmp(str[i],"\0") == 0)
            {
                k = i;
                free(str[k]);
                while(str[k + 1])
                {
                    str[k] = str[k + 1];
                    k++;
                }
                str[k] = NULL;
            }
       }
       else if((str[i][len - 1] == '\'' || str[i][len - 1] == '\"') && is_space(str[i + 1][0]) == 0)
       {
            ft_collect_in_last(&str[i],&str[i + 1]);
            if(ft_strcmp(str[i + 1],"\0") == 0)
            {
                k = i + 1;
                free(str[k]);
                while(str[k + 1])
                {
                    str[k] = str[k + 1];
                    k++;
                }
                str[k] = NULL;
            }
       }
        i++;
    }
    return str;
}

int main(int ac,char **av,char **env)
{
    char **command;
    char *input;
    char **re;
    while(1)
    {
        input = readline("\033[0;35mminishell$ \033[0m");
        if(input == NULL)
            break;
        command = ft_split_command(input);
        // printer(command);
        ft_search_variable(&command,env);
        re = ft_join(command);
        
       printer(re);
        //printf("%s\n",input);
        // list = parsing(input);
        // excution (list);
        // free (list);
        add_history(input);
        free (input);
    }
}
