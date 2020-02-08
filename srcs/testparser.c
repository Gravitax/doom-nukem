/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/08 21:27:19 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void     parse_error(t_cube *data)
{
    clean_exit(data, "doom-nukem: parse error", 0);
}

static void     skip_line(char *str, int *start)
{
    while (str[*start] && str[*start] != '\n')
        ++(*start);
}


//in work progress
static int      get_size(t_cube *data, int start, char *c)
{
    int ret;

    ret = -1;
    while (data->str && data->str[start])
    {
        if (ft_strncmp(data->str + start, c, ft_strlen(c)) == 0)
        {
            skip_line(data->str, &start);
            ++ret;
        }
        else
            clean_exit(data, "cube3d: parse error12", 0);
    }
    return (ret);
}

static void     get_data(t_cube *data, t_mesh *mesh, int *start)
{
    if (!(data->pdata.vertex = (t_vec3d *)malloc(sizeof(t_vec3d)
        * get_size(data, 0, 0, 0))))
            parse_error(data);
    while (isblank(data->str[++(*start)]))
        ;
    
}

static void     handle_space(t_cube *data, int *start)
{
    while (isspace(data->str[*start]))
        ++(*start);
}

static void     handle_comment(t_cube *data, int *start)
{
    while (data->str[*start] == '#')
    {
        skip_line(data->str, start);
        if (data->str[*start] == '\n')
            ++(*start);
    }
}

static void     handle_objectname(t_cube *data, t_mesh *mesh, int *start)
{
    int     end;

    while (isblank(data->str[++(*start)]))
        ;
    end = *start;
    skip_line(data->str, &end);
    if (!(mesh->name = ft_strsub(data->str, *start, end - *start)))
        parse_error(data);
    *start = data->str[end] == '\n' ? end + 1 : end;
}

static void     parsing(t_cube *data, t_mesh *mesh)
{
    int     i;

    i = 0;
    while (data->str[i])
    {
        handle_space(data, &i);
        handle_comment(data, &i);
        if (data->str[i] == 'o')
            handle_objectname(data, mesh, &i);
        handle_space(data, &i);
        handle_comment(data, &i);
        if (data->str[i] == 'v')
            get_data(data, mesh, &i);
        else
            parse_error(data);
        ++i;
    }
}

void            get_object2(t_cube *data, t_mesh *mesh, char *file)
{
    char    *path;

    path = ft_strjoin("/Users/maboye/sgoinfre/doom-nukem/object/", file);
    path = ft_strfjoin(path, ".obj", 1);
    if (!(data->str = ft_readfile(path)))
    {
        ft_strdel(&path);
        clean_exit(data, "cube3d: read error", 0);
    }
    ft_strdel(&path);
    parsing(data, mesh);
}
