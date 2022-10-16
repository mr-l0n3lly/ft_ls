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

typedef struct      s_ls_flag
{
    int             l;
    int             R;
    int             a;
    int             r;
    int             t;
    int             dash;
}                   t_ls_flag;

//typedef struct      s_ls_dir_prop
//{
//    struct dirent   f_info;
//    char            *path;
//}                   t_ls_dir_prop;

typedef struct      s_ls
{
    char            *key;
//    t_ls_dir_prop   *props;
    struct s_ls     *content;
    struct s_ls     *next;
}                   t_ls;

typedef struct      s_ft_ls
{
    t_ls_flag       flags;
    char            **w_dirs;
    t_ls            *content_dict;
}                   t_ft_ls;

t_ls_flag   ft_parse_flags(char **argv, int argc);
int         ft_count_dirs(char **argv);
char        **ft_parse_dirs(char **argv);
void        ft_init(t_ft_ls *ls, char **argv, int argc);
t_ft_ls     *ft_ls(t_ft_ls *ls);

#endif //FT_LS_H
