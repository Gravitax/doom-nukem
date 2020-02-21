/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/21 21:19:13 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void     test_vertexstorage(t_doom *data, t_scene *scene)
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
    printf("tcount: %d\n", data->pdata.tcount);
    clean_exit(data, "vertex good", 1);
}

void            stock_vertex(t_doom *data, t_scene *scene, int *i)
{
    int     nb;
    int     tnb;
    int     tpossible;
    int     v[3];
    int     t[3];

    test_vertexstorage(data, scene);
    tpossible = 0;
    nb = 0;
    tnb = 0;
    ++(*i);
    while (data->str && data->str[*i] && data->str[*i] != '\n')
    {
        while (isblank(data->str[*i]))
            ++(*i);
        if (tpossible == 1 && data->str[*i] == '/')
        {
            while (isblank(data->str[++(*i)]))
                ;
            if (isdigit(data->str[*i]))
            {
                t[tnb] = atoi(data->str + *i);
                while (isdigit(data->str[*i]))
                    ++(*i);
                tpossible = 0;
                ++tnb;
            }
            else
                parse_error(data);
        }
        else if (isdigit(data->str[*i]))
        {
            v[nb] = atoi(data->str + *i);
            while (isdigit(data->str[*i]))
                ++(*i);
            tpossible = 1;
            ++nb;
        }
        else
            parse_error(data);
        if (nb > 3 || tnb > 3)
            parse_error(data);
    }
    data->pdata.s = 0;
    while (isblank(data->str[*i]))
        ++(*i);
    if (nb < 3 || (data->pdata.texture && tnb < 3))
        parse_error(data);
    scene->object[data->pdata.io].size = data->pdata.size++;
    if (data->var.texture)
    {
        scene->object[data->pdata.io].mesh[data->pdata.ti++] = (t_triangle){
            data->pdata.vertex[v[0] - 1],
            data->pdata.vertex[v[1] - 1],
            data->pdata.vertex[v[2] - 1],
            data->pdata.texture[t[0] - 1],
            data->pdata.texture[t[1] - 1],
            data->pdata.texture[t[2] - 1], 0 };
    }
    else
    {
        scene->object[data->pdata.io].mesh[data->pdata.ti++] = (t_triangle){
            data->pdata.vertex[v[0] - 1],
            data->pdata.vertex[v[1] - 1],
            data->pdata.vertex[v[2] - 1], 0 };        
    }
}
