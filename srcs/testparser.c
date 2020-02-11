/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/10 17:41:32 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void            parse_error(t_cube *data)
{
    clean_exit(data, "doom-nukem: parse error", 0);
}

void            skip_line(char *str, int *start)
{
    while (str[*start] && str[*start] != '\n')
        ++(*start);
    if (str[*start] == '\n')
        ++(*start);
}

static void     handle_objectname(t_cube *data, t_obj *object, int *start)
{
    int     end;

    while (isblank(data->str[++(*start)]))
        ;
    end = *start;
    skip_line(data->str, &end);
    if (data->str[--end] == '\n')
        --end;
    if (!(object->name = ft_strsub(data->str, *start, end - *start)))
        parse_error(data);
    *start = data->str[++end] == '\n' ? end + 1 : end ;
}

static void     handle_char(t_cube *data, int *i, char c, t_mesh *mesh)
{
    if (c == '\n' || c == '#')
        skip_line(data, i);
    else if (c == 's')
    {
        data->pdata.s = 1;
        skip_line(data, i);
    }
    else if (c == 'o')
        handle_objectname(data, mesh->object2[++data->pdata.io], i);
    else if (c == 'v')
        handle_vertex(data, mesh, i);
    else if (c == 'f')
        ;
    else if (c == ' ' || c == '\t')
        while (isblank(data->str[*i]))
            ++(*i);
}

static void     parsing(t_cube *data, t_mesh *mesh)
{
    int     i;
    int     j;
    int     error;

    ft_memset(&data->pdata, 0, sizeof(t_pdata));
    data->pdata.c[0] = '\n';
    data->pdata.c[1] = '#';
    data->pdata.c[2] = 'o';
    data->pdata.c[3] = 'v';
    data->pdata.c[4] = 's';
    data->pdata.c[5] = 'f';
    data->pdata.c[6] = ' ';
    data->pdata.c[7] = '\t';
    error = 1;
    i = 0;
    while (data->str[i])
    {
        j = -1;
        while (j < 8)
            if (data->str[i] == data->pdata.c[j])
            {
                handle_char(data, &i, data->pdata.c[j], mesh);
                error = 0;
            }
        if (error == 1)
            parse_error(data);
    }
}

static void     get_totalobject(t_cube *data, t_mesh *mesh)
{
    int     i;

    i = 0;
    while (data->str[i])
    {
        if (data->str[i] == 'o')
            ++data->var.iobj;
        skip_line(data->str, &i);
    }
    if (data->var.iobj == 0)
        data->var.iobj = 1;
    if (!(data->mesh->object2 = (t_obj **)ft_memalloc(sizeof(t_obj *) * data->var.iobj)))
        parse_error(data);
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
    data->var.texture = 0;
    data->pdata.io = -1;
    get_totalobject(data, mesh);
    parsing(data, mesh);
    ft_strdel(&data->str);
    if (data->var.texture == 1)
        ft_memdel((void **)&data->pdata.texture);
    ft_memdel((void **)&data->pdata.vertex);
}
