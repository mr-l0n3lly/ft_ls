//
// Created by Andrei Pavalachi on 25.09.2022.
//

#ifndef FT_LS_H
#define FT_LS_H

/* Outside inc files */
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

/* Own inc files */
#include "libft.h"

/* Temporal library */
#include <stdio.h>

typedef struct      s_ls
{
    struct dirent   f_info;
    char            *path;
    struct s_ls     *context;
    struct s_ls     *next;
}                   t_ls;

typedef struct      s_ft_ls
{
    char            **flags;
    char            **w_dirs;
    t_ls            *contents;
}                   t_ft_ls;

int     ft_count_flags(char **argv);
char    **ft_parse_flags(char **argv);
int     ft_count_dirs(char **argv);
char    **ft_parse_dirs(char **argv);
void    ft_init(t_ft_ls *ls, char **argv);
t_ft_ls *ft_start(t_ft_ls *ls);
void    ft_simple(t_ft_ls *ls);

#endif //FT_LS_H
