#include <dirent.h>
#include <stdio.h>
#include "../libft/libft.h"

char		**ft_tabadd(char **tab, const char *str)
{
	int		i;
	char	**ret;

	if (tab == NULL
	|| !(ret = (char **)ft_memalloc(sizeof(char *)
            * (ft_tablen((void **)tab) + 2))))
		return (NULL);
	i = -1;
	while (tab && tab[++i])
		if (!(ret[i] = ft_strdup(tab[i])))
		{
			ft_tabfree((void **)ret);
			ft_tabfree((void **)tab);
			return (NULL);
		}
	if ((ret[i++] = ft_strdup(str)))
		ret[i] = NULL;
	else
		ft_tabfree((void **)ret);
	ft_tabfree((void **)tab);
	return (ret);
}

int         good_format(char *format)
{
    return ((!ft_strcmp(format, ".myobj")
        || !ft_strcmp(format, ".map")) ? 1 : 0);
}

int         check_format(char ***path_tab, struct dirent *read)
{
    int size;

    size = ft_strlen(read->d_name);
    while (size >= 0 && read->d_name[size] != '.')
        --size;
    if (size < 1)
	return (-1);
    if (good_format(read->d_name + size))
    {
        while (--size >= 0)
            if (!ft_isalnum(read->d_name[size]))
                return (-1);
        if (!(*path_tab = ft_tabadd(*path_tab, read->d_name)))
            return (0);
    }
    return (1);
}

char        **listpath(char *d_path)
{
    char            **path_tab;
    DIR             *dir;
    struct dirent   *read;

    path_tab = NULL;
    dir = opendir(d_path);
    if (dir)
    {
        if (!(path_tab = (char **)ft_memalloc(sizeof(char *) * 1)))
            return (NULL);
        while ((read = readdir(dir)))
            if (!(check_format(&path_tab, read)))
            {
                ft_tabfree((void **)path_tab);
                break ;
            }
        closedir(dir);
    }
    if (path_tab && ft_tablen((void **)path_tab) == 0)
        ft_tabfree((void **)path_tab);
    return (path_tab);
}

int         main(int ac, char **av)
{
    char    **path_tab;

    path_tab = listpath("../wip");
    for (int i = 0; path_tab && path_tab[i]; i++)
        printf("file: %s\n", path_tab[i]);
    return (0);
}
