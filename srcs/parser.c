/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/12 16:40:14 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void            parse_error(t_doom *data)
{
    if (data->str)
		ft_strdel(&data->str);
    if (data->var.texture == 1)
        if (data->pdata.texture)
            ft_memdel((void **)&data->pdata.texture);
	if (data->pdata.vertex)
		ft_memdel((void **)&data->pdata.vertex);
    clean_exit(data, "doom-nukem: parse error", 0);
}

void            skip_line(char *str, int *start)
{
    while (str[*start] && str[*start] != '\n')
        ++(*start);
    if (str[*start] == '\n')
        ++(*start);
}

static void     handle_objectname(t_doom *data, t_obj *object, int *start)
{
    int     end;

    object->i = data->pdata.io;
    while (isblank(data->str[++(*start)]))
        ;
    end = *start;
    skip_line(data->str, &end);
    if (data->str[--end] == '\n')
        --end;
    if (!(object->name = ft_strsub(data->str, *start, end - *start)))
        parse_error(data);
    skip_line(data->str, start);
}

static void     stock_tvertex(t_doom *data, int *t, int *i, int nb)
{
    while (isblank(data->str[++(*i)]))
        ;
    if (isdigit(data->str[*i]))
    {
        *t = atoi(data->str + *i - 1);
        while (isdigit(data->str[*i]))
            ++(*i);
    }
    else
        parse_error(data);
}

static void     stock_vertex(t_doom *data, t_obj *object, int *i)
{
    int     nb;
    int     tpossible;
    int     v[3];
    int     t[3];

    if (data->pdata.io < 0)
        parse_error(data);
    tpossible = 0;
    nb = 0;
    while (nb < 3 && data->str && data->str[*i])
    {
        while (isblank(data->str[++(*i)]))
            ;
        if (tpossible == 1 && data->str[*i] == '/')
        {
            stock_tvertex(data, &t[nb], i, nb);
            tpossible = 0;
        }
        else if (isdigit(data->str[*i]))
        {
            v[nb] = atoi(data->str + *i - 1);
            while (isdigit(data->str[*i]))
                ++(*i);
            tpossible = 1;
            ++nb;
        }
        else
            parse_error(data);
    }
    data->pdata.s = 0;
    while (isblank(data->str[++(*i)]))
        ;
    object->size = data->pdata.size;
    object->mesh[data->pdata.ti++] = (t_triangle){
        data->pdata.vertex[v[0] - 1],
        data->pdata.vertex[v[1] - 1],
        data->pdata.vertex[v[2] - 1],
        data->pdata.texture[t[0] - 1],
        data->pdata.texture[t[1] - 1],
        data->pdata.texture[t[2] - 1] };
}

static void     handle_char(t_doom *data, int *i, char c, t_scene *scene)
{
    printf("char: [%c]\n", c);
    if (c == '\n' || c == '#')
        skip_line(data->str, i);
    else if (c == 's')
    {
        data->pdata.s = 1;
        skip_line(data->str, i);
    }
    else if (c == 'o')
        handle_objectname(data, scene->object[++data->pdata.io], i);
    else if (c == 'v')
        handle_vertex(data, scene, i);
    else if (c == 'f')
        stock_vertex(data, scene->object[data->pdata.io], i);
    else if (c == ' ' || c == '\t')
        while (isblank(data->str[*i]))
            ++(*i);
}

static void     parsing(t_doom *data, t_scene *mesh)
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
    error = 1;
    i = 0;
    while (data->str[i])
    {
        j = -1;
        while (++j < 8)
            if (data->str[i] == data->pdata.c[j])
            {
                handle_char(data, &i, data->pdata.c[j], mesh);
                error = 0;
            }
        if (error == 1)
            parse_error(data);
    }
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
            ++data->scene->iobj;
        skip_line(data->str, &i);
    }
    if (data->scene->iobj == 0)
        data->scene->iobj = 1;
    if (!(data->scene->object = (t_obj **)ft_memalloc(sizeof(t_obj *)
    * data->scene->iobj)))
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
