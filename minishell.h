#ifndef MINISHELL_H
#define MINISHELL_H

#define HEREDOC 1
#define APPEND 2
#define IN 3
#define OUT 4


#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Libft/libft.h"

typedef struct s_dir
{
    int type;
    char    *file_name;
    int is_quoted;
    struct s_dir    *next;
}   t_dir;

typedef struct s_list
{
    char    **command;
    t_dir   *redir;
    struct s_list   *next;
}   t_list;

typedef struct s_data
{
    int c;
    char **com;
    char **command;
    char *input;
}   t_data;

typedef struct s_shell
{
    char **env;
    char **export;
    int exit_status;
    t_data  data;
    t_list *list;
}   t_shell;
// error //
int is_redirection(char *str);
int ft_arry_len(char **str);
int    check_error(char **command);

// help //
int ft_strcmp_len(char *s1,char *s2, int len);
int is_quote(char c);
int ft_close(char *str, char c,int n, int start);
char    *ft_substr_add_space(char *s, int start, int len);
void fix_quotes (char **str);

// split_command//
char **ft_split_command(char *str,int *n);
int ft_check(char *str);
void ft_split_quote(char *str, char ***command);

// expand //
char *ft_replace(char *command,char *var,char *value,int k);
char *get_env_value(char **env, char *var);
char *get_variable(char *command,int pos);
void  ft_search_variable(char ***command,char **env);

// help join //
void    ft_strcpy(char *s1, char *s2);
int is_space_or_quote(char c);
char *ft_remove(char *str,int len_r, int n);
char *get_last_word(char *str);
char *get_first_word(char *str); 

// join //
void    ft_collect_in_first(char **next,char **str);
void    ft_collect_in_last(char **next,char **str);
char **ft_join(char **str);
void    ft_join_quote(char **str);

// split_by_space //

int is_space(char c);
int	check_command(const char *str);
char	**ft_split_by_space_tab(char const *s);
char **ft_split_by_space(char **str);

// filling //
int    filling(char **resu,char *str,char **arry,int i);
void    ft_filling(char *s,char **s1,int lenf,int start);
char **ft_add_command(char **com,int start,int pos,t_list *list);
t_list    *creat_list(char **com,int start,int pos);
void   add_node(t_list *list,char **com,int start,int pos);
t_list    *ft_filling_list(char **com);
char *disable(char *str);
t_dir    *creat_dir_list(int typ,char *name);
void    add_dir_node(t_dir  *redir,int typ,char *name);
void    filling_redir(t_list *list,int typ,char *name,int *c);


// free //
void	free_arr(char **str);
void    free_node(t_list *list);
void    free_list(t_list *list);
#endif