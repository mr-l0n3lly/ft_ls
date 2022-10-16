#include "ft_ls.h"

t_ls_flag   ft_parse_flags(char **argv, int argc)
{
    t_ls_flag       ls_flag;
	int				i;

    ls_flag.R = 0;
    ls_flag.a = 0;
    ls_flag.l = 0;
    ls_flag.r = 0;
    ls_flag.t = 0;
    ls_flag.dash = 0;

	i = 1;
	while(i < argc)
	{
		if (argv[i][0] == '-' && strlen(argv[i]) >= 2)
        {
            if (argv[i][1] == 'l')
            {
                ls_flag.l = 1;
            }

            if (argv[i][1] == 'a')
            {
                ls_flag.a = 1;
            }

            if (argv[i][1] == 'R')
            {
                ls_flag.R = 1;
            }

            if (argv[i][1] == 't')
            {
                ls_flag.t = 1;
            }

            if (argv[i][1] == '-')
            {
                ls_flag.dash = 1;
                break;
            }
        }

		i++;
	}

	return (ls_flag);
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

void	ft_init(t_ft_ls *ls, char **argv, int argc)
{
    ls->flags = ft_parse_flags(argv, argc);
    ls->w_dirs = ft_parse_dirs(argv);
    ls->content_dict = NULL;
}

t_ls *ft_ls_content_new(char *key, t_ls *content)
{
    t_ls *fresh;

    fresh = (t_ls*)malloc(sizeof(t_ls));

    if (fresh == NULL)
        return (NULL);

    if (content == NULL)
    {
        fresh->content = NULL;
    }
    else
    {
        fresh->content = content;
    }

    fresh->key = key;
//    fresh->props = props;
    fresh->next = NULL;

    return (fresh);
}

t_ls *ft_ls_content_add(t_ls *head, t_ls new)
{
    if (head == NULL)
    {
        head = ft_ls_content_new(new.key, new.content);
    }

    t_ls *tmp_head = head;
    t_ls *new_item = (t_ls*)malloc(sizeof(t_ls));

    new_item->key = new.key;
    new_item->content = new.content;
//    new_item->props = new.props;
    new_item->next = new.next;

    while (tmp_head->next)
    {
        tmp_head = tmp_head->next;
    }

    tmp_head->next = new_item;

    return head;
}


t_ls *ft_ls_dir(char *dir, t_ft_ls *ls)
{
    DIR	*dir_p = opendir(dir);
    struct dirent *dirent_p;
    t_ls *content;
    t_ls tmp;

    content = NULL;

    while ((dirent_p = readdir(dir_p)) != NULL)
    {
        if (ls->flags.a == 0 && dirent_p->d_name[0] == '.')
            continue;

        if (content == NULL)
        {
            content = ft_ls_content_new(dirent_p->d_name, NULL);
        }
        else
        {
            tmp.key = dirent_p->d_name;
            tmp.next = NULL;
            tmp.content = NULL;
            content = ft_ls_content_add(content, tmp);
        }

        ft_putstr(dirent_p->d_name);
        ft_putstr("\n");
    }


    return content;
}

t_ls *ft_ls_dir_content(t_ls *content_dict, t_ft_ls *ls)
{
    int i;
    t_ls *result = NULL;

    i = 0;

    while (content_dict)
    {
        if (i == 0)
        {
            result = ft_ls_content_new(content_dict->key, NULL);
            i++;
        }

        result[i].key = content_dict->key;
//        result[i].props = ft_ls_dir(content_dict->key);
        result[i].content = ft_ls_dir(content_dict->key, ls);

        content_dict = content_dict->next;
    }

    return (result);
}

t_ft_ls *ft_ls(t_ft_ls *ls)
{
    int i;
    t_ls tmp;

    i = 0;

    while(ls->w_dirs[i] != NULL)
    {
        tmp.key = ls->w_dirs[i];
//        tmp.props = ft_ls_dir(ls->w_dirs[i]);
        tmp.content = ft_ls_dir(ls->w_dirs[i], ls);
        tmp.next = NULL;

        ls->content_dict = ft_ls_content_add(ls->content_dict, tmp);

        i++;
    }

	return ls;
}


int		main(int argc, char **argv)
{
	t_ft_ls	ls;

    ft_init(&ls, argv, argc);
	ft_ls(&ls);

//    printf("Flags:\n");
//    printf("l %d\n", ls.flags.l);
//    printf("a %d\n", ls.flags.a);
//    printf("R %d\n", ls.flags.R);
//    printf("t %d\n", ls.flags.t);
//    printf("r %d\n", ls.flags.r);
//    printf("- %d\n", ls.flags.dash);
//    printf("Dirs: \n");
//
//    while(*ls.w_dirs)
//    {
//        ft_printf("dir - %s\n", *ls.w_dirs);
//
//        ls.w_dirs = ls.w_dirs + 1;
//    }

	return (0);
}
