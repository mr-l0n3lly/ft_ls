/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobi <andrei.pavalachi@hotmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 00:03:34 by tobi              #+#    #+#             */
/*   Updated: 2020/12/20 02:18:13 by tobi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

#include <stdio.h>


typedef	struct		s_ls
{
	struct	dirent	f_info;
	char			*path;
	struct	s_ls	*content;
	struct	s_ls	*next;

}					t_ls;

typedef struct		s_ft_ls
{
	char			**flags;
	char			**w_dirs;
	t_ls			*contents;
}					t_ft_ls;

int		ft_count_flags(char **argv)
{
	int		flags;
	int		i;

	i = 1;
	flags = 0;
	while(argv[i])
	{
		if((int)ft_strlen(argv[i]) >= 2)
		{
			if(argv[i][0] == '-' && argv[i][1] == '-')
				break;
			else if(argv[i][0] == '-')
				flags++;
		}

		i++;
	}

	return (flags);
}

char	**ft_parse_flags(char **argv)
{
	char			**result;
	int				count;
	int				i;
	int				k;

	count = ft_count_flags(argv);
	result = (char**)malloc(sizeof(char*) * count + 1);

	i = 1;
	k = 0;
	while(argv[i])
	{
		if((int)ft_strlen(argv[i]) >= 2)
		{
			if(argv[i][0] == '-' && argv[i][1] == '-')
			{
				break;
			}
		}

		if(argv[i][0] == '-')
		{
			result[k] = ft_strnew((int)ft_strlen(argv[i]));
			result[k] = ft_strsub(argv[i], 0, ft_strlen(argv[i]));
			k++;
		}

		i++;
	}
	result[k] == NULL;

	return (result);
}

int		ft_count_dirs(char **argv)
{
	int				special;
	int				i;
	int				count;

	special = 0;
	count = 0;
	i = 1;
	while(argv[i])
	{
		if((int)ft_strlen(argv[i]) >= 2)
		{
			if(argv[i][0] == '-' && argv[i][1] == '-')
			{
				special = 1;
				i++;
				continue;
			}
		}

		if(special)
		{
			count++;
		}
		else
		{
			if(argv[i][0] != '-')
			{
				count++;
			}
		}

		i++;
	}

	return (count);
}

char	**ft_parse_dirs(char **argv)
{
	char			**result;
	int				count;
	int				i;
	int				k;
	int				special;

	count = ft_count_dirs(argv);
	
	if(count == 0)
	{
		result = (char**)malloc(sizeof(char*) * 2);
		result[0] = ".";
		result[1] = NULL;

		return (result);
	}

	result = (char**)malloc(sizeof(char*) * count + 1);
	i = 1;
	k = 0;
	special = 0;
	while(argv[i])
	{
		if((int)ft_strlen(argv[i]) >= 2)
		{
			if(argv[i][0] == '-' && argv[i][1] == '-')
			{
				i++;
				special = 1;
				continue;
			}
		}

		if(special)
		{
			result[k] = ft_strnew(ft_strlen(argv[i]));
			result[k] = ft_strsub(argv[i], 0, ft_strlen(argv[i]));
			k++;
		}
		else
		{
			if(argv[i][0] != '-')
			{
				result[k] = ft_strnew(ft_strlen(argv[i]));
				result[k] = ft_strsub(argv[i], 0, ft_strlen(argv[i]));
				k++;
			}
		}

		i++;
	}
	result[k] = NULL;

	return (result);
}

void	ft_init(t_ft_ls *ls, char **argv)
{
	ls->flags = ft_parse_flags(argv);
	ls->w_dirs = ft_parse_dirs(argv);
	ls->contents = NULL;
}

void	ft_start(t_ft_ls *ls)
{
	return;
}

void	ft_simple(t_ft_ls *ls)
{
	ls->flags = NULL;

	ls->w_dirs = (char**)malloc(sizeof(char*) * 2);
	ls->w_dirs[0] = ".";
	ls->w_dirs[1] = NULL;
	ls->contents = NULL;
}

int		main(int argc, char **argv)
{
	t_ft_ls	ls;

	if (argc > 1)
	{
		ft_init(&ls, argv);
	}
	else
	{
		ft_simple(&ls);
	}

	ft_start(&ls);
	
	//DIR	*dirp = opendir(argv[1]);
	//struct dirent *dirc;

	//while ((dirc = readdir(dirp)) != NULL)
	//{
	//	ft_putstr(dirc->d_name);
	//	ft_putstr("\n");
	//}

	return (0);
}
