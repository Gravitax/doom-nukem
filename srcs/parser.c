/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/08 20:19:20 by maboye           ###   ########.fr       */
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
                clean_exit(data, "cube3d: parse error11", 0);
        }
        else
            clean_exit(data, "cube3d: parse error12", 0);
    }
    return (ret);
}

static void     get_triangle(t_cube *data, int i, t_mesh *mesh)
{
    int         nb;
    int         v[3];
    int         t[3];

    nb = 0;
    while (nb < 3 && data->str && data->str[i])
    {
        if (data->str[i] == ' ')
            ++i;
        else if (ft_isdigit(data->str[i]))
        {
            v[nb] = atoi(data->str + i - 1);
            while (ft_isdigit(data->str[i]))
                ++i;
            if (data->str[i] == '/')
            {
                ++i;
                t[nb] = atoi(data->str + i);
                while (ft_isdigit(data->str[i]))
                    ++i;
            }
            ++nb;
            
        }
        else if (data->str[i])
            clean_exit(data, "cube3d: parse error10", 0);
    }
    mesh->size = data->pdata.t;
    mesh->object[data->pdata.t++] = (t_triangle){
        data->pdata.vertex[v[0] - 1],
        data->pdata.vertex[v[1] - 1],
        data->pdata.vertex[v[2] - 1],
        data->pdata.texture[t[0] - 1],
        data->pdata.texture[t[1] - 1],
        data->pdata.texture[t[2] - 1] };
}

static void     get_vertex(t_cube *data, int i, int end)
{
    int         nb;
    float       v[3];

    nb = 0;
    while (nb < end && data->str && data->str[i])
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
            clean_exit(data, "cube3d: parse error9", 0);
    }
    if (end == 3)
        data->pdata.vertex[data->pdata.v++] = (t_vec3d){ v[0], v[1], v[2], 1 };
    else if (end == 2)
        data->pdata.texture[data->pdata.tx++] = (t_vec2d){ v[0], v[1], 1 };
}

static void     fstep(t_cube *data, int x, int i, t_mesh *mesh)
{
    get_vertex(data, i, 2);
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
                clean_exit(data, "cube3d: parse error7", 0);
        }
        else
            clean_exit(data, "cube3d: parse error8", 0);
    }
}

static void     tstep(t_cube *data, int x, int i, t_mesh *mesh)
{
    get_vertex(data, i, 3);
    if (!(data->pdata.texture = (t_vec2d *)ft_memalloc(sizeof(t_vec2d)
            * get_mallocsize(data, x, 't', '\n'))))
        clean_exit(data, "cube3d: malloc error", 0);
    while (data->str && data->str[x])
    {
        if (data->str[x] == 't')
        {
            i = x;
            while (data->str && data->str[x] && data->str[x] != '\n')
                ++x;
            if (data->str[++x] == 't')
                get_vertex(data, i + 2, 2);
            else if (data->str[x] == '\n')
                return (fstep(data, x + 1, i + 2, mesh));
            else
                clean_exit(data, "cube3d: parse error3", 0);
        }
        else
            clean_exit(data, "cube3d: parse error4", 0);
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
                get_vertex(data, i + 2, 3);
            else if (data->str[x] == '\n')
                return (tstep(data, x + 1, i + 2, mesh));
            else
                clean_exit(data, "cube3d: parse error1", 0);
        }
        else
            clean_exit(data, "cube3d: parse error2", 0);
    }
}

static void     parsing(t_cube *data, t_mesh *mesh)
{
    if (!(data->pdata.vertex = (t_vec3d *)ft_memalloc(sizeof(t_vec3d)
            * get_mallocsize(data, 0, 'v', '\n'))))
        clean_exit(data, "cube3d: malloc error", 0);
    data->pdata.t = 0;
    data->pdata.tx = 0;
    data->pdata.v = 0;
    parsefile(data, mesh);
    ft_memdel((void **)&data->pdata.texture);
    ft_memdel((void **)&data->pdata.vertex);
    ft_strdel(&data->str);
}

void            get_object(t_cube *data, t_mesh *mesh, char *file)
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
