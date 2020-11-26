#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int		main(int argc, char **argv)
{
	DIR	*dirp = opendir(argv[1]);
	struct dirent *dirc;

	while ((dirc = readdir(dirp)) != NULL)
	{
		ft_putstr(dirc->d_name);
		ft_putstr("\n");
	}

	return (0);
}
