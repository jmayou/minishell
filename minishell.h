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

typedef struct s_shell
{
    char **env;
    char **export;
    t_list *list;
    int exit_status;
}   t_shell;

 void	free_arr(char **str);
#endif