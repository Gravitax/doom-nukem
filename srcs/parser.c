/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/12/16 16:14:55 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int      get_mallocsize(t_cube *data, int start, char c, char end)
{
    int ret;

    ret = -1;
    while (data->str && data->str[start])
    {
        if (data->str[start] == c)
        {
            while (data->str && data->str[start] && data->str[start] != '\n')
                ++start;
            ++ret;
            if (data->str[++start] == c)
                continue ;
            else if (data->str[start] == end)
                return (ret + 1);
            else
                clean_exit(data, "cube3d: parse error", 0);
        }
        else
            clean_exit(data, "cube3d: parse error", 0);
    }
    return (ret);
}

static void     get_triangle(t_cube *data, int i, t_mesh *mesh)
{
    int         nb;
    int         vi[3];

    nb = 0;
    while (nb < 3 && data->str && data->str[i])
    {
        if (data->str[i] == ' ')
            ++i;
        else if (ft_isdigit(data->str[i]))
        {
           vi[nb++] = atoi(data->str + i - 1); 
           while (ft_isdigit(data->str[i]))
                ++i;
        }
        else if (data->str[i])
            clean_exit(data, "cube3d: parse error", 0);
    }
    mesh->size = data->ti;
    mesh->object[data->ti++] = (t_triangle){ 
        data->vector.vertex[vi[0] - 1],
        data->vector.vertex[vi[1] - 1],
        data->vector.vertex[vi[2] - 1] };
}

static void     get_vertex(t_cube *data, int i)
{
    int         nb;
    float       v[3];

    nb = 0;
    while (nb < 3 && data->str && data->str[i])
    {
        if (data->str[i] == '-' || data->str[i] == ' ')
            ++i;
        else if (ft_isdigit(data->str[i]))
        {
           v[nb++] = atof(data->str + i - 1); 
           while (ft_isdigit(data->str[i]) || data->str[i] == '.')
                ++i;
        }
        else if (data->str[i])
            clean_exit(data, "cube3d: parse error", 0);
    }
    data->vector.vertex[data->vi++] = (t_vec3d){ v[0], v[1], v[2], 1 };
}

static void     step2(t_cube *data, int x, int i, t_mesh *mesh)
{
    get_vertex(data, i);
    if (!(mesh->object = (t_triangle *)ft_memalloc(sizeof(t_triangle)
            * get_mallocsize(data, x, 'f', '\0'))))
        clean_exit(data, "cube3d: malloc error", 0);
    while (data->str && data->str[x])
    {
        if (data->str[x] == 'f')
        {
            i = x;
            while (data->str && data->str[x] && data->str[x] != '\n')
                ++x;
            if (data->str[++x] == 'f')
                get_triangle(data, i + 2, mesh);
            else if (data->str[x] == '\n' || data->str[x] == '\0')
                return (get_triangle(data, i + 2, mesh));
            else
                clean_exit(data, "cube3d: parse error", 0);
        }
        else
            clean_exit(data, "cube3d: parse error", 0);
    }
}

static void     parsefile(t_cube *data, t_mesh *mesh)
{
    int     i;
    int     x;

    x = 0;
    while (data->str && data->str[x])
    {
        if (data->str[x] == 'v')
        {
            i = x;
            while (data->str && data->str[x] && data->str[x] != '\n')
                ++x;
            if (data->str[++x] == 'v')
                get_vertex(data, i + 2);
            else if (data->str[x] == '\n')
                return (step2(data, x + 1, i + 2, mesh));
            else
                clean_exit(data, "cube3d: parse error", 0);
        }
        else
            clean_exit(data, "cube3d: parse error", 0);
    }
}

void            get_object(t_cube *data, t_mesh *mesh, char *file)
{
    char    *path;

    path = ft_strjoin("/sgoinfre/goinfre/Perso/maboye/cube3d/object/", file);
    path = ft_strfjoin(path, ".obj", 1);
    if (!(data->str = ft_readfile(path)))
    {
        ft_strdel(&path);
        clean_exit(data, "cube3d: read error", 0);
    }
    ft_strdel(&path);
    if (!(data->vector.vertex = (t_vec3d *)ft_memalloc(sizeof(t_vec3d)
            * get_mallocsize(data, 0, 'v', '\n'))))
        clean_exit(data, "cube3d: malloc error", 0);
    data->ti = 0;
    data->vi = 0;
    parsefile(data, mesh);
    ft_memdel((void **)&data->vector.vertex);
    ft_strdel(&data->str);
}
