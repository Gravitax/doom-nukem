/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/25 18:57:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void     handle_objectname(t_doom *data, t_scene *scene, int *start)
{
    int     end;

    data->pdata.s = 0;
    data->pdata.ti = 0;
    scene->object[++data->pdata.io].i = data->pdata.io;
    scene->object[data->pdata.io].mesh = NULL;
    while (isblank(data->str[++(*start)]))
        ;
    end = *start;
    skip_line(data->str, &end);
    end = data->str[end - 1] == '\n' ? end - 1 : end;
    if (!(scene->object[data->pdata.io].name = ft_strsub(data->str,
    *start, end - *start)))
        parser_error(data);
    skip_line(data->str, start);
}

static void     handle_char(t_doom *data, int *i, t_scene *scene)
{
    char    c;

    c = data->str[*i];
    if (c == '\n' || c == '#' || c == 'm')
        skip_line(data->str, i);
    else if (c == 's')
    {
        data->pdata.s = 1;
        skip_line(data->str, i);
    }
    else if (c == 'o')
        handle_objectname(data, scene, i);
    else if (c == 'v')
        parser_handlevertex(data, scene, i);
    else if (c == 'f')
        parser_stockvertex(data, scene, i);
    else if (c == 'u')
        parser_mtlassign(data, scene, i);
    else if (c == ' ' || c == '\t')
        while (isblank(data->str[*i]))
            ++(*i);
}

static void     test_meshstorage(t_doom *data, t_scene *scene)
{
    int     o = -1;

    return ;
    while (++o < scene->iobj)
    {
        int     i = -1;
        puts("---------------------------------------------------------");
        printf("name: %s\n", scene->object[o].name);
        while (++i < scene->object[o].size)
        {
            int     j = -1;
            printf("[vi: (%d)]\n", i);
            while (++j < 3)
            {
                printf("x: %f, y: %f, z: %f, w: %f\n", scene->object[o].mesh[i].v[j].x,
                    scene->object[o].mesh[i].v[j].y,
                    scene->object[o].mesh[i].v[j].z,
                    scene->object[o].mesh[i].v[j].w);
                printf("u: %f, v: %f, w: %f\n",
                    scene->object[o].mesh[i].t[j].u,
                    scene->object[o].mesh[i].t[j].v,
                    scene->object[o].mesh[i].t[j].w);
                puts("-------------------");
            }
        }
    }
    clean_exit(data, "bugbugbug", 1);
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
        if (parser_goodchar(data, data->str[i]) == 0)
            parser_error(data);
        else if (data->str[i] == 'o')
            ++scene->iobj;
        skip_line(data->str, &i);
    }
    if (scene->iobj < 1)
        parser_error(data);
    if (!(scene->object = (t_obj *)ft_memalloc(sizeof(t_obj) * scene->iobj)))
        parser_error(data);
}

static void     parsing(t_doom *data, t_scene *scene)
{
    int     i;

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
    data->pdata.c[8] = 'm';
    data->pdata.c[9] = 'u';
    get_totalobject(data, scene);
    i = 0;
    while (data->str[i])
    {
        if (parser_goodchar(data, data->str[i]))
            handle_char(data, &i, scene);
        else
            parser_error(data);
    }
    test_meshstorage(data, scene);
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
    parsing(data, scene);
    ft_strdel(&data->str);
    ft_memdel((void **)&data->pdata.texture);
    ft_memdel((void **)&data->pdata.vertex);
}
