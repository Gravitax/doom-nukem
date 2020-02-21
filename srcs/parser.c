/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/21 21:12:59 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void     handle_objectname(t_doom *data, t_scene *scene, int *start)
{
    int     end;

    data->pdata.s = 0;
    scene->object[++data->pdata.io].i = data->pdata.io;
    while (isblank(data->str[++(*start)]))
        ;
    end = *start;
    skip_line(data->str, &end);
    end = data->str[end - 1] == '\n' ? end - 1 : end;
    if (!(scene->object[data->pdata.io].name = ft_strsub(data->str,
    *start, end - *start)))
        parse_error(data);
    skip_line(data->str, start);
}

static void     handle_char(t_doom *data, int *i, char c, t_scene *scene)
{
    if (c == '\n' || c == '#')
        skip_line(data->str, i);
    else if (c == 's')
    {
        data->pdata.s = 1;
        skip_line(data->str, i);
    }
    else if (c == 'o')
        handle_objectname(data, scene, i);
    else if (c == 'v')
        handle_vertex(data, scene, i);
    else if (c == 'f')
        stock_vertex(data, scene, i);
    else if (c == ' ' || c == '\t')
        while (isblank(data->str[*i]))
            ++(*i);
}

static void     test_meshstorage(t_doom *data, t_scene *scene)
{
    return ;
    int     i = -1;

    while (++i < data->pdata.ti)
    {
        int     j = -1;
        printf("[vi: (%d)]\n", i);
        while (++j < 3)
        {
            printf("x: %f, y: %f, z: %f, w: %f\n", scene->object[data->pdata.io].mesh[i].v[j].x,
                scene->object[data->pdata.io].mesh[i].v[j].y,
                scene->object[data->pdata.io].mesh[i].v[j].z,
                scene->object[data->pdata.io].mesh[i].v[j].w);
            printf("u: %f, v: %f, w: %f\n",
                scene->object[data->pdata.io].mesh[i].t[j].u,
                scene->object[data->pdata.io].mesh[i].t[j].v,
                scene->object[data->pdata.io].mesh[i].t[j].w);
            puts("-------------------");
        }
    }
}

static void     parsing(t_doom *data, t_scene *scene)
{
    int     i;
    int     j;
    int     error;

    ft_memset(&data->pdata, 0, sizeof(t_pdata));
    data->pdata.io = -1;
    data->pdata.c[0] = '\n';
    data->pdata.c[1] = '#';
    data->pdata.c[2] = 'o';
    data->pdata.c[3] = 'v';
    data->pdata.c[4] = 's';
    data->pdata.c[5] = 'f';
    data->pdata.c[6] = ' ';
    data->pdata.c[7] = '\t';
    i = 0;
    while (data->str[i])
    {
        error = 1;
        j = -1;
        while (++j < 8)
            if (data->str[i] == data->pdata.c[j])
            {
                handle_char(data, &i, data->pdata.c[j], scene);
                error = 0;
            }
        if (error == 1)
            parse_error(data);
    }
    test_meshstorage(data, scene);
}

static void     get_totalobject(t_doom *data, t_scene *scene)
{
    int     i;

    i = 0;
    scene->iobj = 0;
    while (data->str[i])
    {
        while (isblank(data->str[i]))
            ++i;
        if (data->str[i] == 'o')
            ++scene->iobj;
        skip_line(data->str, &i);
    }
    if (scene->iobj < 1)
        parse_error(data);
    if (!(scene->object = (t_obj *)ft_memalloc(sizeof(t_obj) * scene->iobj)))
        parse_error(data);
}

void            get_object(t_doom *data, t_scene *scene, char *file)
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
    get_totalobject(data, scene);
    parsing(data, scene);
    ft_strdel(&data->str);
    if (data->var.texture == 1)
        ft_memdel((void **)&data->pdata.texture);
    ft_memdel((void **)&data->pdata.vertex);
}
