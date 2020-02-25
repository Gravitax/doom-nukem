/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_faces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/25 19:20:07 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void     test_vertexstorage(t_doom *data)
{
    return ;
    puts("-------------------------------");
    int i = data->pdata.vcount;
    int j = data->pdata.vtcount;
    while (i--)
        printf("i: %d, x: %f, y: %f, z: %f, w: %f\n", i,
            data->pdata.vertex[i].x,
            data->pdata.vertex[i].y,
            data->pdata.vertex[i].z,
            data->pdata.vertex[i].w);
    puts("\n");
    while (j--)
        printf("j: %d, u: %f, v: %f, w: %f\n", j,
            data->pdata.texture[j].u,
            data->pdata.texture[j].v,
            data->pdata.texture[j].w);
    clean_exit(data, "vertex good", 1);
}

static void     init_mesh(t_doom *data, t_scene *scene, int i)
{
    int f;

    f = 0;
    while (data->str[i])
    {
        while (isblank(data->str[i]))
            ++i;
        if (parser_goodchar(data, data->str[i]) == 0)
            parser_error(data);
        else if (data->str[i] == 'o')
            break ;
        else if (data->str[i] == 'f')
            ++f;
        skip_line(data->str, &i);
    }
    scene->object[data->pdata.io].size = f;
    f = sizeof(t_triangle) * f;
    if (!(scene->object[data->pdata.io].mesh = (t_triangle *)malloc(f)))
        parser_error(data);
}

static void     stock_triangle(t_doom *data, t_scene *scene)
{
    if (data->var.texture)
    {
        scene->object[data->pdata.io].mesh[data->pdata.ti++] = (t_triangle){
            data->pdata.vertex[data->pdata.v[0] - 1],
            data->pdata.vertex[data->pdata.v[1] - 1],
            data->pdata.vertex[data->pdata.v[2] - 1],
            data->pdata.texture[data->pdata.t[0] - 1],
            data->pdata.texture[data->pdata.t[1] - 1],
            data->pdata.texture[data->pdata.t[2] - 1], 0 };
    }
    else
    {
        scene->object[data->pdata.io].mesh[data->pdata.ti++] = (t_triangle){
            data->pdata.vertex[data->pdata.v[0] - 1],
            data->pdata.vertex[data->pdata.v[1] - 1],
            data->pdata.vertex[data->pdata.v[2] - 1], 0 };        
    }    
}

static void     handle_vtex(t_doom *data, int *i, int *tpossible)
{
    while (isblank(data->str[++(*i)]))
        ;
    if (isdigit(data->str[*i]))
    {
        data->pdata.t[data->pdata.tnb] = atoi(data->str + *i);
        while (isdigit(data->str[*i]))
            ++(*i);
        *tpossible = 0;
        ++data->pdata.tnb;
    }
    else
        parser_error(data);
}

static void     get_vertexindex(t_doom *data, int *i)
{
    int tpossible;

    tpossible = 0;
    data->pdata.nb = 0;
    data->pdata.tnb = 0;
    ++(*i);
    while (data->str && data->str[*i] && data->str[*i] != '\n')
    {
        while (isblank(data->str[*i]))
            ++(*i);
        if (tpossible == 1 && data->str[*i] == '/')
            handle_vtex(data, i, &tpossible);
        else if (isdigit(data->str[*i]))
        {
            data->pdata.v[data->pdata.nb] = atoi(data->str + *i);
            while (isdigit(data->str[*i]))
                ++(*i);
            tpossible = 1;
            ++data->pdata.nb;
        }
        else
            parser_error(data);
        if (data->pdata.nb > 3 || data->pdata.tnb > 3)
            parser_error(data);
    }
}

void            parser_stockvertex(t_doom *data, t_scene *scene, int *i)
{
    test_vertexstorage(data);
    if (scene->object[data->pdata.io].mesh == NULL)
        init_mesh(data, scene, *i);
    if (data->pdata.vcount == 0)
        parser_error(data);
    get_vertexindex(data, i);
    data->pdata.s = 0;
    while (isblank(data->str[*i]))
        ++(*i);
    if (data->pdata.nb < 3 || data->pdata.v[0] > data->pdata.vi
    || data->pdata.v[1] > data->pdata.vi || data->pdata.v[2] > data->pdata.vi)
        parser_error(data);
    else if (data->pdata.texture
    && (data->pdata.tnb < 3 || data->pdata.t[0] > data->pdata.vti
    || data->pdata.t[1] > data->pdata.vti || data->pdata.t[2] > data->pdata.vti))
        parser_error(data);
    stock_triangle(data, scene);
}
